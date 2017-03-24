/**
 * file: smokers.cpp
 *
 * compile: $ make -f makeconexam.mk smokers
 *          $ g++ -o smokers smokers.cpp -pthread
 *
 * author:  Juan Francisco Cardona Mc'Cormick 
 * purpose: This is an implementation of smokers problem
 *
 * create: 30/03/2015
 *
 * History of Modificacions:
 *  23/03/2017 - Adding coments and makefile. Cleaning code.
 *               
 */
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>

using namespace std;

const int SMOKERS = 4; // smokers: 3 plus agents: 1

enum smokerType { smokerT, smokerP, smokerM, agent };

sem_t sem[SMOKERS];

const char* smokerType[] = { "smoker with tabaco",
                             "smoker with paper",
                             "smoker with matches"
};
		      
void*
smokers(void *arg) {
  int* smokerId;
  
  smokerId = (int *)arg;
  
  while (true) {
    
    sem_wait(&sem[*smokerId]);
    
    int rand = random();

    cout << "smoking: " << smokerType[*smokerId] << endl;

    sleep((rand % 3) + 1);
    
    sem_post(&sem[agent]);
  }
  
  int *ret = new int;
  
  *ret = 0;
  
  return ret;
}

void*
agentThread(void *args) {
  
  while(true) {

    int rand = random();
    
    sem_post(&sem[rand % 3]);
    sem_wait(&sem[agent]);
  }
}

int
main() {
  pthread_t smokersThread[SMOKERS];

  srand(time(NULL));
  
  for (int i = 0; i < SMOKERS; i++) {

    sem_init(&sem[i], 0, 0);
  }

  for (int i = 0; i < (SMOKERS - 1); i++) {
    int *arg = new int;
    
    *arg = i;
    
    pthread_create(&smokersThread[i], NULL, smokers, arg); 
  }

  pthread_create(&smokersThread[SMOKERS-1], NULL, agentThread,NULL);

  int *pointer;
  for (int i = 0; i < SMOKERS; i++) {
    
    pthread_join(smokersThread[i], (void **) &pointer);
  }
  
  return 0;
}

