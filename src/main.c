#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "transaction.h"
#include "transaction_types.h"
#include "transaction_producer.h"
#include "transaction_consumer.h"
#include "transaction_queue.h"
#include "transaction_list.h"
#include "parser.h"
#include "customer_list.h"
#include "customer.h"

/* 
  This buffer is shared among producers and consumers.
    - Producers generate transactions and enqueue them.
    - Consumers dequeue transactions and process them.
*/
TransactionQueue *ptr_transaction_buffer;

TransactionList *ptr_transaction_list;

CustomerList *ptr_customer_list = NULL;

pthread_cond_t cond_transaction_in_progress = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_empty_buffer = PTHREAD_COND_INITIALIZER;

int main()
{
  // Initialize PRG seed
  srand(time(NULL));

  ptr_customer_list = readCustomerData();

  // TODO: Validate customer array

  // Initialize the buffer with 100 transactions capacity
  ptr_transaction_buffer = createQueue(400);
  ptr_transaction_list = initializeTransactionList();

  pthread_t *producer_threads = initializeTransactionProducers(2);
  pthread_t *consumer_threads = initializeTransactionConsumers(2);

  joinProducerThreads(producer_threads);
  joinConsumerThreads(consumer_threads);

  return 0;
}