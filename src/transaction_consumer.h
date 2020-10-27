#ifndef TRANSACTION_CONSUMER_H
#define TRANSACTION_CONSUMER_H

pthread_t *initializeTransactionConsumers(int consumer_quantity);

void joinConsumerThreads(pthread_t consumer_threads[]);
void *transactionConsumer(void *consumer_id);
int costumerHasTransactionInProgress(int sender_id);

#endif