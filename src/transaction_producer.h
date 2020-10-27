#ifndef TRANSACTION_PRODUCER_H
#define TRANSACTION_PRODUCER_H

pthread_t *initializeTransactionProducers(int producer_quantity);

void *transactionProducer(void *producer_id);
void joinProducerThreads(pthread_t producer_threads[]);
void wakeUpConsumers();

#endif