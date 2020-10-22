#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "transaction.h"
#include "transaction_producer.h"

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

    printf("%d: %d, %d, %d, %d\n", *(int *)producer_id, transaction.sender_id, transaction.receiver_id, transaction.value, transaction.type);

    sleep(3);
  }
}