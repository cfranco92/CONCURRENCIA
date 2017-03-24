/**
 * file: garden.cpp
 *
 * compile: $ make -f makeconexam.mk garden
 *          $ g++ -o garden garden.cpp -pthread
 *
 * author:  Juan Francisco Cardona Mc'Cormick 
 * purpose: This is an implementation of garden problem
 *
 * create: 30/03/2015
 *
 * History of Modificacions:
 *  23/03/2017 - Adding coments and makefile. Cleaning code.
 */
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>

using namespace std;

int counter = 0;
sem_t sec;
const int MAX_VISITORS=100;

void*
visitors(void *arg) {
  int *ret = new int;
  
  // Visitor enter to the garden
  sem_wait(&sec);
  counter++;
  cout << "Actual value: " 
       << counter 
       << " thread-id: " << pthread_self() << endl; 
  sem_post(&sec);

  // Visitor visiting the garden
  int rand = random();
  sleep((rand % 10) + 1);
  sem_wait(&sec);
  counter--;
  
  cout << "Actual value: " 
       << counter 
       << " thread-id: " << pthread_self() << endl;

  // Visitor leaving the garden
  sem_post(&sec);
  
  *ret = 0;
  return ret;
}

void*
admin(void *arg) {

  for (;;) {
    // admin
    int rand = random();
    sleep((rand % 2) + 1);
    
    // Seeing visitor number
    sem_wait(&sec);
    cout << "Counter: " << counter << endl;
    sem_post(&sec);
  }
}

int
main() {
  pthread_t visitorsThread[MAX_VISITORS + 1];
  srand(time(NULL));
  sem_init(&sec, 0, 1);
  int i;
  for (i = 0; i < MAX_VISITORS; i++) {
    pthread_create(&visitorsThread[i], NULL, visitors, NULL); 
  }

  pthread_create(&visitorsThread[i], NULL, admin, NULL);

  int *pointer;

  for (int i = 0; i < MAX_VISITORS; i++) {
    pthread_join(visitorsThread[i], (void **) &pointer);
  }

  pthread_join(visitorsThread[MAX_VISITORS], (void **) &pointer);
  return 0;
}
