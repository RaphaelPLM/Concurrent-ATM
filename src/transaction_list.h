#ifndef TRANSACTION_LIST_H
#define TRANSACTION_LIST_H

#include "transaction.h"

typedef struct TransactionNode
{
  Transaction *data;
  struct TransactionNode *next;
} TransactionNode;

typedef struct
{
  TransactionNode *head;
  TransactionNode *tail;
  int node_count;
} TransactionList;

TransactionList *initializeTransactionList();
void pushTransactionIntoList(Transaction *transaction, TransactionList *list);
TransactionNode *generateTransactionNode(Transaction *transaction);
int isTransactionListEmpty(TransactionList *list);
int searchSenderInList(int sender_id, TransactionList *list);
void removeTransactionFromListByPosition(TransactionList *list, int pos);

#endif