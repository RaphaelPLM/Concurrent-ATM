#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include "transaction.h"
#include "transaction_types.h"
#include "transaction_producer.h"

int main()
{
  srand(time(NULL));

  initializeTransactionProducers(10);

  return 0;
}