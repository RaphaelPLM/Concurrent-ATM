#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "transaction.h"
#include "transaction_producer.h"
#include "transaction_queue.h"

#define TRUE 1
#define FALSE 0

extern TransactionQueue *ptr_transaction_buffer;

pthread_mutex_t enqueue_lock = PTHREAD_MUTEX_INITIALIZER;

void initializeTransactionProducers(int producer_quantity)
{
  pthread_t producer_threads[producer_quantity];

  for (int i = 0; i < producer_quantity; i++)
  {
    int *producer_id = (int *)malloc(sizeof(int));
    *producer_id = i;

    int error = pthread_create(&producer_threads[i], NULL, transactionProducer, (void *)(producer_id));

    if (error)
    {
      printf("An error occurred while creating thread %d\n", *(int *)producer_id);
      exit(1);
    }
  }

  pthread_join(producer_threads[0], NULL);
}

void *transactionProducer(void *producer_id)
{
  while (1)
  {
    Transaction transaction = generateTransactionData();

    // Enqueuing may imply a race condition when the buffer is almost full.
    pthread_mutex_lock(&enqueue_lock);
      enqueue(ptr_transaction_buffer, transaction, TRUE);
    pthread_mutex_unlock(&enqueue_lock);

    sleep(3);
  }
}