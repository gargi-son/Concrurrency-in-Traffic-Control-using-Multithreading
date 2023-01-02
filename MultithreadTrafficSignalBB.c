
#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include "../BBBio_lib/BBBiolib.h"
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <assert.h>
#include <sys/utsname.h>

//Defining LED ports on Beaglebone Black
#define REDLIGHTSIG1 8,8
#define YELLOWLIGHTSIG1 8,7
#define GREENLIGHTSIG1 8,12
#define REDLIGHTSIG2 8,17
#define YELLOWLIGHTSIG2 8,16
#define GREENLIGHTSIG2 8,15
#define SWITCHTOSIG1 8,11
#define SWITCHTOSIG2 8,14

//Defining threads, mutexes and shared variables
pthread_mutex_t lock;
pthread_t thread1, thread2, thread3, thread4, thread5;

int8_t  c1=0, c2=0, f1=0, f2=0;

//Function to print the system configuration and team member names
void systemConfigPrint(){
    struct utsname sysInfo;
    if(uname(&sysInfo)!=0)
   {
      perror("uname doesn't return 0, so there is an error");
      exit(EXIT_FAILURE);
   }
    (void) printf("System Name = %s\n", sysInfo.sysname);
    (void) printf("Node Name = %s\n", sysInfo.nodename);
    (void) printf("Machine Name= %s\n", sysInfo.machine);
    (void) printf("Student Names = %s\n", "Aastha, Gargi, Preeti, Uday");
}

//Function that changes light sequence from Green to Red for Signal 1
void *threadFunctionGreentoRedSig1 ( ){

    printf(" Green to Red for Signal 1\n");
    pin_low(REDLIGHTSIG1);
    pin_low(GREENLIGHTSIG1);
    pin_low(YELLOWLIGHTSIG1);
    int8_t i=0;
    while(i<20){
        
        printf("Green light for Signal 1 ON\n");
        pin_high(GREENLIGHTSIG1);
        sleep(20);
        pin_low(GREENLIGHTSIG1);
        printf("Yellow light for Signal 1 ON\n");
        pin_high(YELLOWLIGHTSIG1);
        sleep(5);
        pin_low(YELLOWLIGHTSIG1);
        printf("Red light for Signal 1 ON\n");
        pin_high(REDLIGHTSIG1);
        sleep(5);
        pin_low(REDLIGHTSIG1);
        printf("Red light for Signal 1 ON\n");
        pin_high(REDLIGHTSIG1);
        sleep(15);
        pthread_mutex_lock(&lock);
        //Flag to check if time remaining is <5s in the normal sequence
        f1=1;
        pthread_mutex_unlock(&lock);
        sleep(5);
        pthread_mutex_lock(&lock);
        f1=0;
        pthread_mutex_unlock(&lock);
        pin_low(REDLIGHTSIG1);
        printf("Red light for Signal 1 ON\n");
        pin_high(REDLIGHTSIG1);
        sleep(5);
        pin_low(REDLIGHTSIG1);
        printf("Red light for Signal 1 ON\n");
        pin_high(REDLIGHTSIG1);
        sleep(5);
        pin_low(REDLIGHTSIG1);
        i++;
    }

    return 0;

}

//Function that changes light sequence from Red to Green for Signal 1
void *threadFunctionRedtoGreenSig1 ( ){
    
    pin_low(REDLIGHTSIG1);
    pin_low(GREENLIGHTSIG1);
    pin_low(YELLOWLIGHTSIG1);

    printf(" Red to Green for Signal 1\n");
    int8_t i=0;
    while(i<20){
        printf("Red light for Signal 1 ON\n");
        pin_high(REDLIGHTSIG1);
        sleep(15);
        pthread_mutex_lock(&lock);
        //Flag to check if time remaining is <5s in the normal sequence
        f1=1;
        pthread_mutex_unlock(&lock);
        sleep(5);
        pthread_mutex_lock(&lock);
        f1=0;
        pthread_mutex_unlock(&lock);
        pin_low(REDLIGHTSIG1);
        printf("Red light for Signal 1 ON\n");
        pin_high(REDLIGHTSIG1);
        sleep(5);
        pin_low(REDLIGHTSIG1);
        printf("Red light for Signal 1 ON\n");
        pin_high(REDLIGHTSIG1);
        sleep(5);
        pin_low(REDLIGHTSIG1);
        printf("Green light for Signal 1 ON\n");
        pin_high(GREENLIGHTSIG1);
        sleep(20);
        pin_low(GREENLIGHTSIG1);
        printf("Yellow light for Signal 1 ON\n");
        pin_high(YELLOWLIGHTSIG1);
        sleep(5);
        pin_low(YELLOWLIGHTSIG1);
        printf("Red light for Signal 1 ON\n");
        pin_high(REDLIGHTSIG1);
        sleep(5);
        pin_low(REDLIGHTSIG1);
        i++;
    }

    return 0;

}

//Function that changes light sequence from Green to Red for Signal 2
void *threadFunctionGreentoRedSig2 ( ){

    printf(" Green to Red for Signal 2\n");
    pin_low(GREENLIGHTSIG2);
    pin_low(YELLOWLIGHTSIG2);
    pin_low(REDLIGHTSIG2);
    int8_t i=0;
    while(i<20){
        
        printf("Green light for Signal 2 ON\n");
        pin_high(GREENLIGHTSIG2);
        sleep(20);
        pin_low(GREENLIGHTSIG2);
        printf("Yellow light for Signal 2 ON\n");
        pin_high(YELLOWLIGHTSIG2);
        sleep(5);
        pin_low(YELLOWLIGHTSIG2);
        printf("Red light for Signal 2 ON\n");
        pin_high(REDLIGHTSIG2);
        sleep(5);
        pin_low(REDLIGHTSIG2);
        printf("Red light for Signal 2 ON\n");
        pin_high(REDLIGHTSIG2);
        sleep(15);

        //mutex protection for the shared data 
        pthread_mutex_lock(&lock);
        //Flag to check if time remaining is <5s in the normal sequence
        f2=1;
        pthread_mutex_unlock(&lock);
        sleep(5);
        pthread_mutex_lock(&lock);
        f2=0;
        pthread_mutex_unlock(&lock);
        pin_low(REDLIGHTSIG2);
        printf("Red light for Signal 2 ON\n");
        pin_high(REDLIGHTSIG2);
        sleep(5);
        pin_low(REDLIGHTSIG2);
        printf("Red light for Signal 2 ON\n");
        pin_high(REDLIGHTSIG2);
        sleep(5);
        pin_low(REDLIGHTSIG2);
        i++;
    }

    return 0;

}


//Function that changes light sequence from Red to Green for Signal 2
void *threadFunctionRedtoGreenSig2 ( ){
    
    pin_low(GREENLIGHTSIG2);
    pin_low(YELLOWLIGHTSIG2);
    pin_low(REDLIGHTSIG2);

    printf(" Red to Green for Signal 2\n");
    int8_t i=0;
    while(i<20){
        printf("Red light for Signal 2 ON\n");
        pin_high(REDLIGHTSIG2);
        sleep(15);
        pthread_mutex_lock(&lock);
        //Flag to check if time remaining is <5s in the normal sequence
        f2=1;
        pthread_mutex_unlock(&lock);
        sleep(5);
        pthread_mutex_lock(&lock);
        f2=0;
        pthread_mutex_unlock(&lock);
        pin_low(REDLIGHTSIG2);
        printf("Red light for Signal 2 ON\n");
        pin_high(REDLIGHTSIG2);
        sleep(5);
        pin_low(REDLIGHTSIG2);
        printf("Red light for Signal 2 ON\n");
        pin_high(REDLIGHTSIG2);
        sleep(5);
        pin_low(REDLIGHTSIG2);
        printf("Green light for Signal 2 ON\n");
        pin_high(GREENLIGHTSIG2);
        sleep(20);
        pin_low(GREENLIGHTSIG2);
        printf("Yellow light for Signal 2 ON\n");
        pin_high(YELLOWLIGHTSIG2);
        sleep(5);
        pin_low(YELLOWLIGHTSIG2);
        printf("Red light for Signal 2 ON\n");
        pin_high(REDLIGHTSIG2);
        sleep(5);
        pin_low(REDLIGHTSIG2);
        i++;
    }

    return 0;

}

//Function that reads whether the Switch 1 for Signal 1 is pressed or not.
void *threadFunctionReadSwitch1 ( ){

    int8_t i=0;
    while(1){
        pthread_mutex_lock(&lock);
        int8_t ff1 = f1;
        pthread_mutex_unlock(&lock);

        //checks if the wait sensor is pressed and the normal sequence is not in the last 5 secs, increasing the wait counter 1         
        while(is_high(SWITCHTOSIG1) && ff1==0){
            
        pthread_mutex_lock(&lock);
        c1++;
        pthread_mutex_unlock(&lock);
        printf("Switch 1 pressed %d\n", c1);
        sleep(1);         
        }
        c1=0;
        sleep(1);
        i++;
    }

    return 0;

}

//Function that reads whether the Switch 2 for Signal 2 is pressed or not.
void *threadFunctionReadSwitch2 ( ){

    int8_t i=0;
    while(1){
        
        pthread_mutex_lock(&lock);
        int8_t ff2 = f2;
        pthread_mutex_unlock(&lock);
        
        //checks if the wait sensor is pressed and the normal sequence is not in the last 5 secs, increasing the wait counter 2
        while(is_high(SWITCHTOSIG2) && ff2==0){
            
        pthread_mutex_lock(&lock);
        c2++;
        pthread_mutex_unlock(&lock);
        printf("Switch 2 pressed %d\n", c1);
        sleep(1);   
        }
        
        c2=0;
        sleep(1);
        i++;
    }

    return 0;

}

//Function for thread which reads the counter of switches and check wheteher normal sequence is in last 5 seconds.
//It will switches the threads and restarts the sequence of siganls according to push buttons.
void *threadFunctionReadCount ( ){

    int8_t i=0;
    while(1){
        
        //mutex protection for the shared data which is reading the wait counter
        pthread_mutex_lock(&lock);
        int8_t t1 = c1;
        pthread_mutex_unlock(&lock);
        
        //checks if the wait counter 1 timer is greater than 5 sec, then turns the signal1 to green 
        if(t1>=5){
            pthread_cancel(thread1);
            pthread_cancel(thread4);
            printf("Thread execution started again by Signal 1 \n");
            pthread_create (&thread1, NULL, &threadFunctionGreentoRedSig1, NULL);
            pthread_create (&thread4, NULL, &threadFunctionRedtoGreenSig2, NULL);
            pthread_mutex_lock(&lock);
             c1 = 0;
            pthread_mutex_unlock(&lock);
        }

        //mutex protection for the shared data which is reading the wait counter        
        pthread_mutex_lock(&lock);
        int8_t t2 = c2;
        pthread_mutex_unlock(&lock);
 
        //checks if the wait counter 1 timer is greater than 5 sec, then turns the signal1 to green 
        if(t2>=5 ){
            pthread_cancel(thread1);
            pthread_cancel(thread4);
            printf("Thread execution started again by Signal 2 \n");
            pthread_create (&thread1, NULL, &threadFunctionGreentoRedSig2, NULL);
            pthread_create (&thread4, NULL, &threadFunctionRedtoGreenSig1, NULL);
            pthread_mutex_lock(&lock);
             c2 = 0;
            pthread_mutex_unlock(&lock);
        }

    }

    return 0;

}

//Main function of the traffic signal that is executed
int8_t main(void)
{
    
	iolib_init();
	iolib_setdir(SWITCHTOSIG1, BBBIO_DIR_IN);
	iolib_setdir(GREENLIGHTSIG1, BBBIO_DIR_OUT);
	iolib_setdir(YELLOWLIGHTSIG1, BBBIO_DIR_OUT);
	iolib_setdir(REDLIGHTSIG1, BBBIO_DIR_OUT);
	iolib_setdir(SWITCHTOSIG2, BBBIO_DIR_IN);
	iolib_setdir(YELLOWLIGHTSIG2, BBBIO_DIR_OUT);
	iolib_setdir(REDLIGHTSIG2, BBBIO_DIR_OUT);
	iolib_setdir(GREENLIGHTSIG2, BBBIO_DIR_OUT);
    
    systemConfigPrint();
    
    //Creating Threads
	
	pthread_create (&thread1, NULL, &threadFunctionRedtoGreenSig1, NULL);
	
	pthread_create (&thread4, NULL, &threadFunctionGreentoRedSig2, NULL);

    pthread_create (&thread2, NULL, &threadFunctionReadCount, NULL);

    pthread_create (&thread3, NULL, &threadFunctionReadSwitch1, NULL);

    pthread_create (&thread5, NULL, &threadFunctionReadSwitch2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);
   
    iolib_free();
	
	return(0);
}


