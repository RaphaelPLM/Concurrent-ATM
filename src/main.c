#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "transaction.h"
#include "transaction_types.h"
#include "transaction_producer.h"
#include "transaction_queue.h"

/* 
  This buffer is shared among producers and consumers.
    - Producers generate transactions and enqueue them.
    - Consumers dequeue transactions and process them.
*/
TransactionQueue *ptr_transaction_buffer;

int main()
{
  srand(time(NULL));
  
  // Initialize the buffer with 100 transactions capacity
  ptr_transaction_buffer = createQueue(100);

  initializeTransactionProducers(10);

  return 0;
}