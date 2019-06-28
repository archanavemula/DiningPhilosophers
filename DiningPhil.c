#Write program in C language using Pthreads API to simulate the following IPC problem. Refer to Section 5.9.4 for specific instructions on mutex lock and semaphore.
#Ans:Used threads and semaphores
#If there are multiple files in your submission, you need to provide a makefile.
#Ans:One file only
#Include the compilation command with required options at the very beginning of your code.
#gcc -lpthread diningPhil.c 
#(20 pts) Make sure to use mutex locks or semaphores, or other tools, to synchronize the tasks correctly.
#Ans:Yes, no dead occurs
#(5 pts) Your program should include the design of the project, with specific answers to the following questions. Your answer to the questions must 
#match your implementation. You can answer these question at the beginning of your source file as comments.
#How many threads/processes are there?
#Ans:1 process and 5 threads
#What does each thread simulate?
#ans: each thread will initialize each philosopher and allows him to pick up or put back the cchopstick
#Will each thread be blocked at some time of simulation?
#Ans: Yes, when chopstick is not available they will be put on lock using sem_wait() on that philosopher
#If yes, explain the circumstances.When will a blocked thread be waked up, and by whom?
#Ans:
#How many mutex locks/semaphores are there in your code, what is the purpose for having each?
# Ans:Here there are two semaphores : Mutex and a semaphore array for the philosophers. 
#Mutex is used such that no two philosophers may access the pickup or putdown at the same time. 
#The array is used to control the behavior of each philosopher.
#How does your program terminate?
#ans: donno
#(5 pts) Use appropriate code indentation and comments, referring to any sample code from textbook.
#ans: need to check again
#(5 pts) Introduce randomness in your code. The thread/process needs to sleep for a random period of time to simulate the execution of any critical 
#section and reminder section. You can use rand(), sleep() functions. 
#Ans: Using sleep function when philosopher is eating of picked up the fork().
#(5 pts) Display messages to the screen to show the state of the system. A good way to validate your program running correctly is to perform some 
#simple output messages to show the state of the system. You can experiment with these messages, but in general you want to demonstrate what each 
#thread is doing, and use some identifier, such as an integer number, to identify each thread.
#Ans:Yes , displaying all the messages to the screen by printing what each philosopher is doing
#(5 pts) If your program needs any arguments in command line (for example, number of services), you need to prompt proper message for the arguments 
#and also validate the input.
#Ans:donno..need to add a constant which can be an input from outside that will terminate the program
#(5 pts) You need to consider how to terminate your program. There are many options. For example, terminate after serving a given number of times 
#(each service here means thatone philosopher finishes eating once). You need to explain this in your code.
#donno- need to add the constant.


#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <stdlib.h>
#include <unistd.h>


int state_of_philosopher[5]; 
int philosophers[5] = { 0, 1, 2, 3, 4 }; 
sem_t mutex; 
sem_t S[5]; 

#define THINKING 2 
#define HUNGRY 1 
#define EATING 0 

#define Num 5

#define L_CHOP (phil_num + 4) % Num 
#define R_CHOP (phil_num + 1) % Num 
  


int no_of_processes = 0;

int main() 
{ 
    int i; 
    pthread_t t_id[Num]; 
  
    // initialize the semaphores 
    sem_init(&mutex, 0, 1); 
  
    for (i = 0; i < Num; i++) 
        sem_init(&S[i], 0, 0); 
  
    for (i = 0; i < Num; i++) { 
        // create philosopher processes 
        pthread_create(&t_id[i], NULL, runner, &phil[i]); 
        printf(" %d  Philosopher is thinking state\n", i + 1); 
    } 
  
    for (i = 0; i < N; i++) 
      pthread_join(thread_id[i], NULL); 

   printf(" Process Number  ", ++no_of_processes); 
} 

void* runner(void* num) 
{  
    while (1) { 
        int* i = num; 
        sleep(1); 
        pickup_forks(*i); 
        sleep(0); 
        return_forks(*i); 
    } 
} 


// take the chopsticks from the table
void pickup_forks(int phil_num) 
{ 
    sen_wait(&mutex); 
    state[phil_num] = HUNGRY;  
    printf(" %d  Philosopher is Hungry\n", phil_num + 1); 
   
    if (state[phil_num] == HUNGRY && state[L_CHOP] != EATING && state[R_CHOP] != EATING) { 
        state[phil_num] = EATING; 
        sleep(2); 
        printf("%d  Philosopher is Eating\n", phil_num + 1); 
        sem_post(&S[phil_num]); 
    } 
  
    sem_post(&mutex); 
    sem_wait(&S[phil_num]); 
    sleep(1); 
} 


void test(int phil_num) 
{ 

    if (state[phil_num] == HUNGRY && state[L_CHOP] != EATING && state[R_CHOP] != EATING) { 
       
        state[phil_num] = EATING; 
  
        sleep(2); 
  
        printf("Philosopher %d is Eating\n", phil_num + 1); 
  
        sem_post(&S[phil_num]); 
    } 
} 
    
// put down chopsticks again back to the table
void return_forks(int phil_num) 
{ 
  
    sem_wait(&mutex); 
  
    // state that thinking 
    state[phil_num] = THINKING; 
  
    printf("Philosopher %d putting fork %d and %d down\n", 
           phil_num + 1, LEFT + 1, phil_num + 1); 
    printf("Philosopher %d is thinking\n", phil_num + 1); 
  
    test(LEFT); 
    test(RIGHT); 
  
    sem_post(&mutex); 
} 
  
  
