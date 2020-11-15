#ifndef CUSTOMER_LIST_H
#define CUSTOMER_LIST_H

#include "customer.h"

typedef struct CustomerNode
{
  Customer *data;
  struct CustomerNode *next;
} CustomerNode;

typedef struct
{
  CustomerNode *head;
  CustomerNode *tail;
  int node_count;
} CustomerList;

CustomerList *initializeCustomerList();
void pushCustomerIntoList(Customer *customer, CustomerList *list);
CustomerNode *generateCustomerNode(Customer *customer);
int isCustomerListEmpty(CustomerList *list);
Customer* searchCustomerInList(int customer_id, CustomerList *list);
void removeCustomerFromListByPosition(CustomerList *list, int pos); // TODO: Adapt to remove by ID

#endif