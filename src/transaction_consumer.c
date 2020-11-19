#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "transaction.h"
#include "customer.h"
#include "transaction_consumer.h"
#include "transaction_queue.h"
#include "transaction_list.h"
#include "transaction_types.h"
#include "customer_list.h"

#define TRUE 1
#define FALSE 0

extern TransactionQueue *ptr_transaction_buffer;
extern TransactionList *ptr_transaction_list;
extern CustomerList *ptr_customer_list;

pthread_mutex_t dequeue_lock = PTHREAD_MUTEX_INITIALIZER;

extern pthread_cond_t cond_transaction_in_progress;
extern pthread_cond_t cond_empty_buffer;

int thread_id;

// Store sender ID's from transactions that are being processed
int *sender_processing_in_progress;

pthread_t *initializeTransactionConsumers(int consumer_quantity)
{
  pthread_t *consumer_threads = malloc(sizeof(pthread_t) * consumer_quantity);

  for (int i = 0; i < consumer_quantity; i++)
  {
    int *consumer_id = (int *)malloc(sizeof(int));
    *consumer_id = i;

    int error = pthread_create(&consumer_threads[i], NULL, transactionConsumer, (void *)(consumer_id));

    if (error)
    {
      printf("An error occurred while creating thread %d\n", *(int *)consumer_id);
      exit(1);
    }
  }

  return consumer_threads;
}

void *transactionConsumer(void *consumer_id)
{
  thread_id = *(int *) consumer_id;

  while (1)
  {
    // Lock dequeue_lock to ensure that the same transaction cannot by dequeued by two or more consumers.
    pthread_mutex_lock(&dequeue_lock);
      while(isTransactionQueueEmpty(ptr_transaction_buffer))
      {
        printf("%d: There are no transactions to be processed. Consumer %d should wait.\n\n", thread_id, thread_id);
        
        pthread_cond_wait(&cond_empty_buffer, &dequeue_lock);
      }
      
      Transaction *transaction = dequeue(ptr_transaction_buffer, TRUE);

      while (costumerHasTransactionInProgress(transaction->sender_id) || costumerHasTransactionInProgress(transaction->receiver_id))
      {
        printf("%d: Ongoing transaction by sender %d.\n\n", thread_id, transaction->sender_id);
        
        pthread_cond_wait(&cond_transaction_in_progress, &dequeue_lock);
      }

      pushTransactionIntoList(transaction, ptr_transaction_list);
    pthread_mutex_unlock(&dequeue_lock);

    //Process transaction
    processTransaction(transaction);

    sleep(1);

    int current_transaction_index = searchSenderInList(transaction->sender_id, ptr_transaction_list);

    removeTransactionFromListByPosition(ptr_transaction_list, current_transaction_index);

    pthread_cond_broadcast(&cond_transaction_in_progress);

    sleep(1);
  }
}

int costumerHasTransactionInProgress(int sender_id)
{
  if (searchSenderInList(sender_id, ptr_transaction_list) == -1)
    return 0;

  return 1;
}

void joinConsumerThreads(pthread_t consumer_threads[])
{
  pthread_join(consumer_threads[0], NULL);
}

void processTransaction(Transaction* transaction)
{
  switch(transaction->type)
  {
    case Withdraw:
      withdraw(transaction->value, transaction->sender_id);
      break;
    case Deposit:
      deposit(transaction->value, transaction->sender_id);
      break;
    case Transfer:
      transfer(transaction->value, transaction->sender_id, transaction->receiver_id);
      break;
    default:
      printf("InvalidTypeException\n");
  }
}

void withdraw(double amount, int customer_id)
{
  Customer *customer = searchCustomerInList(customer_id, ptr_customer_list);

  if(customer == NULL)
  {
    printf("%d: Invalid customer. Withdraw failed.\n", thread_id);

    sleep(1);

    return;
  }

  if(customer->balance >= amount)
  {
    customer->balance -= amount;

    printf("%d: Withdraw executed successfully. Customer %d new balance is: %.2lf\n\n", thread_id, customer->id, customer->balance);
  }
  else
  {
    printf("%d: Withdraw failed. Customer %d has insufficient funds.\n\n.", thread_id, customer->id);
  }

  sleep(1);
}

void deposit(double amount, int customer_id)
{
  Customer *customer = searchCustomerInList(customer_id, ptr_customer_list);

  if(customer == NULL)
  {
    printf("%d: Deposit failed. Invalid customer.\n", thread_id);

    sleep(1);

    return;
  }
  
  customer->balance += amount;

  printf("%d: Deposit executed successfully. Customer %d new balance is: %.2lf\n\n", thread_id, customer->id, customer->balance);

  sleep(1);
}

void transfer(double amount, int sender_id, int receiver_id)
{
  Customer *sender = searchCustomerInList(sender_id, ptr_customer_list);
  Customer *receiver = searchCustomerInList(receiver_id, ptr_customer_list);

  if(sender == NULL || receiver == NULL)
  {
    printf("%d: Deposit failed. Invalid sender or receiver.\n", thread_id);

    sleep(1);

    return;
  }

  if(sender->balance >= amount)
  {
    sender->balance -= amount;
    receiver->balance += amount;
    printf("%d: Transfer executed successfully. \n\tCustomer %d new balance is: %.2lf\n\tCustomer %d new balance is: %.2lf\n\n", thread_id, sender->id, sender->balance, receiver->id, receiver->balance);

  }
}