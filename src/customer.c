#include <stdio.h>
#include <stdlib.h>
#include "customer.h"
#include "string.h"

Customer* generateCustomer(int id, char *name, double balance)
{
  Customer *customer = malloc(sizeof(Customer));

  customer->id = id;
  strcpy(customer->name, name);
  customer->balance = balance;

  return customer;
}