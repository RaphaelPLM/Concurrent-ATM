#ifndef TRANSACTION_PRODUCER_H
#define TRANSACTION_PRODUCER_H

#include "transaction_queue.h"

void initializeTransactionProducers(int producer_quantity);
void *transactionProducer(void *producer_id);

#endif