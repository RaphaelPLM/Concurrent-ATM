#include <stdio.h>
#include <stdlib.h>
#include "customer_list.h"

CustomerList *initializeCustomerList()
{
  CustomerList *customer_list = malloc(sizeof(CustomerList));

  customer_list->node_count = 0;
  customer_list->head = NULL;
  customer_list->tail = NULL;

  return customer_list;
}

void pushCustomerIntoList(Customer *customer, CustomerList *list)
{
  CustomerNode *customer_node = generateCustomerNode(customer);

  if (isCustomerListEmpty(list))
  {
    list->head = customer_node;
    list->tail = customer_node;
  }
  else
  {
    CustomerNode *tail = list->tail;

    tail->next = customer_node;

    list->tail = customer_node;
  }

  list->node_count++;

  return;
}

Customer* searchCustomerInList(int customer_id, CustomerList *list)
{
  CustomerNode *current_node = list->head;

  if(current_node == NULL)
  {
    return NULL;
  }

  int pos = 0;

  while(current_node != NULL)
  {
    if(current_node->data->id == customer_id)
    {
      return current_node->data;
    }

    current_node = current_node->next;
    pos++;
  }

  return NULL;
}

void removeCustomerFromListByPosition(CustomerList *list, int pos)
{
  CustomerNode *current_node = list->head;
  CustomerNode *previous_node = NULL;
  
  // Iterate through the list until reach the position of the node to be removed.
  for (int i = 0; i <= pos; i++)
  { 
    if(i == pos)
    {
      CustomerNode *next = current_node->next;     

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

CustomerNode *generateCustomerNode(Customer *customer)
{
  CustomerNode *node = malloc(sizeof(CustomerNode));

  node->data = customer;
  node->next = NULL;

  return node;
}

int isCustomerListEmpty(CustomerList *list)
{
  return list->node_count == 0 && list->head == NULL && list->tail == NULL;
}