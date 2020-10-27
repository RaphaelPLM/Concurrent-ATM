#include <stdio.h>
#include <stdlib.h>
#include "transaction_list.h"

TransactionList *initializeTransactionList()
{
  TransactionList *transaction_list = malloc(sizeof(TransactionList));

  transaction_list->node_count = 0;
  transaction_list->head = NULL;
  transaction_list->tail = NULL;

  return transaction_list;
}

void pushTransactionIntoList(Transaction *transaction, TransactionList *list)
{
  TransactionNode *transaction_node = generateTransactionNode(transaction);

  if (isTransactionListEmpty(list))
  {
    list->head = transaction_node;
    list->tail = transaction_node;
  }
  else
  {
    TransactionNode *tail = list->tail;

    tail->next = transaction_node;

    list->tail = transaction_node;
  }

  list->node_count++;

  return;
}

int searchSenderInList(int sender_id, TransactionList *list)
{
  TransactionNode *current_node = list->head;

  if(current_node == NULL)
  {
    return -1;
  }

  int pos = 0;

  while(current_node != NULL)
  {
    if(current_node->data->sender_id == sender_id)
    {
      return pos;
    }

    current_node = current_node->next;
    pos++;
  }

  return -1;
}

void removeTransactionFromListByPosition(TransactionList *list, int pos)
{
  TransactionNode *current_node = list->head;
  TransactionNode *previous_node = NULL;
  
  // Iterate through the list until reach the position of the node to be removed.
  for (int i = 0; i <= pos; i++)
  { 
    if(i == pos)
    {
      TransactionNode *next = current_node->next;     

      if(pos == 0)
      {
        list->head = next;
      }

      if(pos == list->node_count - 1)
      {
        list->tail = previous_node;
      }

      if(previous_node != NULL)
      {
        previous_node->next = next;
      }

      list->node_count--;

      free(current_node);

      break;
    }
    
    previous_node = current_node;
    current_node = current_node->next;
  }
}

TransactionNode *generateTransactionNode(Transaction *transaction)
{
  TransactionNode *node = malloc(sizeof(TransactionNode));

  node->data = transaction;
  node->next = NULL;

  return node;
}

int isTransactionListEmpty(TransactionList *list)
{
  return list->node_count == 0 && list->head == NULL && list->tail == NULL;
}