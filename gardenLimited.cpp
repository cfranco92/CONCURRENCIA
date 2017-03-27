/**    CRISTIAN FRANCO
 * file: gardenLimited.cpp
 *
 * compile: $ make -f makeconexam.mk gardenLimited
 *          $ g++ -o gardenLimited gardenLimited.cpp -pthread
 *
 * author:  Juan Francisco Cardona Mc'Cormick 
 * purpose: This is an implementation of gardenLimited problem
 *
 * create: 30/03/2015
 *
 * History of Modificacions:
 *  23/03/2017 - Adding coments and makefile
 */
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>

using namespace std;

const int MAX_VISITORS=100;
const int MAX_VISITORS_INSIDE=30;
int counter = 0;
sem_t gardenSem;
sem_t counterSec;

void*
visitors(void *arg) {
  int *ret = new int;

  sem_wait(&gardenSem);
  sem_wait(&counterSec);
  counter++;
  cout << "Actual value: " 
       << counter 
       << " thread-id: " << pthread_self() << endl;
  sem_post(&counterSec);
 
  int rand = random();
  sleep((rand % 3) + 1); 
  sem_wait(&counterSec);
  counter--;
  sem_post(&counterSec);
  sem_post(&gardenSem);
  *ret = 0;
  return ret;
}

void*
admin(void *arg) {

  for (;;) {
    // admin
    int rand = random();
    sleep((rand % 2) + 1);
    // Ver usuarios
    sem_wait(&counterSec);
    cout << "Counter: " << counter << endl;
    sem_post(&counterSec);
  }
}

int
main() {
  pthread_t visitorsThread[MAX_VISITORS + 1];
  srand(time(NULL));

  sem_init(&counterSec, 0, 1);
  sem_init(&gardenSem, 0, MAX_VISITORS_INSIDE);

  int i;
  for (i = 0; i < MAX_VISITORS; i++) {
    
    pthread_create(&visitorsThread[i], NULL, visitors, NULL); 
  }

  pthread_create(&visitorsThread[MAX_VISITORS], NULL, admin, NULL);

  int *pointer;

  for (int i = 0; i < MAX_VISITORS; i++) {
    pthread_join(visitorsThread[i], (void **) &pointer);
  }

  pthread_join(visitorsThread[MAX_VISITORS], (void **) &pointer);
  return 0;
}

