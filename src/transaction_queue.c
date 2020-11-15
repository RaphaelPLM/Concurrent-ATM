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
  queue->transactions = malloc(sizeof(Transaction *) * capacity);

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

void enqueue(TransactionQueue *queue, Transaction* transaction, int verbose)
{
  if (isTransactionQueueFull(queue))
  {
    if(verbose)
      printf("Error: The buffer is full.\n\n");
    
    return; 
  }

  queue->back = (queue->back + 1) % queue->capacity;
  queue->transactions[queue->back] = transaction;
  queue->size = queue->size + 1;

  if (verbose)
  {
    printf("Transaction enqueued: \n\tSender ID: %d\n\tReceiver ID: %d\n\tValue: %d\n\tType: %d\n\nThe queue has now %d transactions.\n\n", transaction->sender_id, transaction->receiver_id, transaction->value, transaction->type, queue->size);
  }
}

Transaction* dequeue(TransactionQueue *queue, int verbose)
{
  if (isTransactionQueueEmpty(queue))
    return generateInvalidTransaction();

  Transaction *transaction = queue->transactions[queue->front];

  queue->front = (queue->front + 1) % queue->capacity;
  queue->size = queue->size - 1;

  if(verbose)
    printf("Transaction dequeued: \n\tSender ID: %d\n\tReceiver ID: %d\n\tValue: %d\n\tType: %d\n\nThe queue has now %d transactions.\n\n", transaction->sender_id, transaction->receiver_id, transaction->value, transaction->type, queue->size);

  return transaction;
}