#ifndef TRANSACTION_QUEUE_H
#define TRANSACTION_QUEUE_H

#include "transaction.h"

typedef struct
{
  int front, back, size;
  unsigned capacity;
  Transaction *transactions;
} TransactionQueue;

TransactionQueue *createQueue(unsigned capacity);
void enqueue(TransactionQueue *queue, Transaction transaction, int verbose);
Transaction dequeue(TransactionQueue *queue);
int isTransactionQueueFull(TransactionQueue *queue);
int isTransactionQueueEmpty(TransactionQueue *queue);

#endif