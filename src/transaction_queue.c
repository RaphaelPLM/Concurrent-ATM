#include <stdio.h>
#include <stdlib.h>
#include "transaction_queue.h"

TransactionQueue *createQueue(unsigned capacity)
{
  TransactionQueue *queue = (TransactionQueue *)malloc(sizeof(TransactionQueue));

  queue->capacity = capacity;
  queue->front = 0;
  queue->back = capacity - 1;
  queue->size = 0;
  queue->transactions = (Transaction *)malloc(sizeof(Transaction) * capacity);

  return queue;
}

int isTransactionQueueFull(TransactionQueue *queue)
{
  return (queue->size == queue->capacity);
}

int isTransactionQueueEmpty(TransactionQueue *queue)
{
  return (queue->size == 0);
}

void enqueue(TransactionQueue *queue, Transaction transaction, int verbose)
{
  if (isTransactionQueueFull(queue))
  {
    if(verbose)
      printf("\nError: The buffer is full.\n");
    
    return;
  }

  queue->back = (queue->back + 1) % queue->capacity;
  queue->transactions[queue->back] = transaction;
  queue->size = queue->size + 1;

  if (verbose)
  {
    printf("Transaction enqueued: \n");
    printf("\tSender ID: %d\n", transaction.sender_id);
    printf("\tReceiver ID: %d\n", transaction.receiver_id);
    printf("\tValue: %d\n", transaction.value);
    printf("\tType: %d\n\n", transaction.type);
  }
}

Transaction dequeue(TransactionQueue *queue)
{
  if (isTransactionQueueEmpty(queue))
    return;

  Transaction transaction = queue->transactions[queue->front];

  queue->front = (queue->front + 1) % queue->capacity;
  queue->size = queue->size - 1;

  return transaction;
}