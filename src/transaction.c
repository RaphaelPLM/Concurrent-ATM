#include <stdio.h>
#include <stdlib.h>
#include "transaction.h"

#define COSTUMER_QUANTITY 5
#define MAX_TRANSACTION_VALUE 1000

Transaction *generateTransactionData()
{
  int sender_id = generateCustomerId(COSTUMER_QUANTITY);
  int value = generateValue(MAX_TRANSACTION_VALUE);
  int receiver_id;

  do
  {
    receiver_id = generateCustomerId(COSTUMER_QUANTITY);
  } while (!validateDistinctSenderReceiver(sender_id, receiver_id)); // Prevents receiver_id being equal to sender_id.

  int type = generateTransactionType();

  Transaction *transaction = malloc(sizeof(Transaction));

  transaction->sender_id = sender_id;
  transaction->receiver_id = receiver_id;
  transaction->value = value;
  transaction->type = type;

  return transaction;
}

Transaction generateTransactionDataFromValues(int sender_id, int receiver_id, int Value, int type)
{
  // TODO
}

Transaction *generateInvalidTransaction()
{
  Transaction *invalid_transaction; 

  invalid_transaction->sender_id = -1;
  invalid_transaction->receiver_id = -1;
  invalid_transaction->value = -1;
  invalid_transaction->type = -1;

  return invalid_transaction;
}

int generateCustomerId(int max_value)
{
  return rand() % max_value + 1;
}

int generateValue(int max_value)
{
  return (rand() % (max_value / 10 + 1)) * 10;
}

int generateTransactionType()
{
  return rand() % 3 + 1;
}

// TODO: Validate based on transaction type
int validateTransaction(Transaction *transaction)
{
  return (validateSender(transaction->sender_id) && validateReceiver(transaction->receiver_id) && validateDistinctSenderReceiver(transaction->sender_id, transaction->receiver_id) && validateType(transaction->type));
}

static int validateSender(int sender_id)
{
  return sender_id > 0 && sender_id <= COSTUMER_QUANTITY;
}

static int validateReceiver(int receiver_id)
{
  return receiver_id > 0 && receiver_id <= COSTUMER_QUANTITY;
}

static int validateDistinctSenderReceiver(int sender_id, int receiver_id)
{
  return sender_id != receiver_id;
}

static int validateType(int type)
{
  return type > 0 && type <= 3;
}

