#ifndef TRANSACTION_H
#define TRANSACTION_H

typedef struct
{
  int sender_id;
  int receiver_id;
  int value;
  int type;
} Transaction;

Transaction *generateTransactionData();
Transaction generateTransactionDataFromValues(int sender_id, int receiver_id, int amount, int type);
Transaction *generateInvalidTransaction();

int generateCustomerId(int max_value);
int generateValue(int max_value);
int generateTransactionType();
int validateTransaction(Transaction *transaction);

static int validateSender(int sender_id);
static int validateReceiver(int receiver_id);
static int validateDistinctSenderReceiver(int sender_id, int receiver_id);
static int validateType(int type);

#endif