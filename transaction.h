#ifndef TRANSACTION_H
#define TRANSACTION_H

typedef struct
{
  int sender_id;
  int receiver_id;
  int value;
  int type;
} Transaction;

Transaction generateTransactionData();
Transaction generateTransactionDataFromValues(int sender_id, int receiver_id, int amount, int type);
int generateCustomerId(int max_value);
int generateValue(int max_value);
int generateTransactionType();

#endif