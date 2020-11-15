#ifndef TRANSACTION_CONSUMER_H
#define TRANSACTION_CONSUMER_H

pthread_t *initializeTransactionConsumers(int consumer_quantity);

void joinConsumerThreads(pthread_t consumer_threads[]);
void *transactionConsumer(void *consumer_id);
int costumerHasTransactionInProgress(int sender_id);
void withdraw(double amount, int customer_id);
void processTransaction(Transaction* transaction);
void deposit(double amount, int customer_id);
void transfer(double amount, int sender_id, int receiver_id);

#endif