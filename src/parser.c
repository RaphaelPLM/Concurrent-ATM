#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"
#include "customer_list.h"

CustomerList* readCustomerData()
{
  FILE *fp = fopen("../data/customers.txt", "r");

  if (fp != NULL)
  {
    int id;
    char name[20];
    double balance;

    CustomerList* customer_list = initializeCustomerList();

    while (fscanf(fp, "%d %s %lf", &id, name, &balance) == 3)
    {    
      Customer *customer = generateCustomer(id, name, balance);

      pushCustomerIntoList(customer, customer_list);
    }
    
    fclose(fp);

    return customer_list;
  }
  else
  {
    perror("customers.txt");
  }
}