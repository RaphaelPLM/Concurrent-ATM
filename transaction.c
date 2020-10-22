#include <stdio.h>
#include <stdlib.h>
#include "transaction.h"

#define NUMBER_COSTUMERS 5
#define MAX_TRANSACTION_VALUE 100

Transaction generateTransactionData()
{
  int sender_id = generateCustomerId(NUMBER_COSTUMERS);
  int value = generateValue(MAX_TRANSACTION_VALUE);
  int receiver_id;

  do
  {
    receiver_id = generateCustomerId(NUMBER_COSTUMERS);
  } while (receiver_id == sender_id); // Prevents receiver_id being equal to sender_id.

  int type = generateTransactionType();

  Transaction transaction =
      {
          .sender_id = sender_id,
          .receiver_id = receiver_id,
          .value = value,
          .type = type};

  return transaction;
}

Transaction generateTransactionDataFromValues(int sender_id, int receiver_id, int Value, int type)
{
  // TODO
}

int generateCustomerId(int max_value)
{
  return rand() % max_value + 1;
}

int generateValue(int max_value)
{
  return (rand() % (max_value + 1)) * 10;
}

int generateTransactionType()
{
  return rand() % 3 + 1;
}