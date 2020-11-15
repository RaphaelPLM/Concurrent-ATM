#ifndef CUSTOMER_H
#define CUSTOMER_H

typedef struct {
  int id;
  char name[20];
  double balance;
} Customer;

Customer* generateCustomer(int id, char *name, double balance);

#endif