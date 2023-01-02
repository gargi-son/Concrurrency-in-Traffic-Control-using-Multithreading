
#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <assert.h>
#include <sys/utsname.h>

//Defining threads, mutexes and shared variables
pthread_mutex_t lock;
pthread_t thread1, thread2, thread3, thread4, thread5;

int c1=0, c2=0, f1=0, f2=0;

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
void *threadFunctionGreentoRedSig1 (void*){
   
    int i=0;
    while(i<20){
        pthread_mutex_lock(&lock);
        f1=0;
        pthread_mutex_unlock(&lock);
        printf("Sig1 Green Light on\n");
        sleep(20);
        printf("Sig1 Yellow Light on\n");
        sleep(5);
        printf("Sig1 Red Light on\n");
        sleep(5);
        printf("Sig1 Red Light on\n");
        sleep(15);
        pthread_mutex_lock(&lock);
        //Flag to check if time remaining is <5s in the normal sequences
        f1=1;
        pthread_mutex_unlock(&lock);
        sleep(5);
        pthread_mutex_lock(&lock);
        f1=0;
        pthread_mutex_unlock(&lock);
        printf("Sig1 Red Light on\n");
        sleep(5);
        printf("Sig1 Red Light on\n");
        sleep(5);
        i++;
    }

    return 0;

}

//Function that changes light sequence from Red to Green for Signal 1
void *threadFunctionRedtoGreenSig1 (void*){
    
    int i=0;
    while(i<20){
        pthread_mutex_lock(&lock);
        f1=0;
        pthread_mutex_unlock(&lock);
        printf("Sig1 Red Light on\n");
        sleep(15);
        pthread_mutex_lock(&lock);
        f1=1;
        pthread_mutex_unlock(&lock);
        sleep(5);
        pthread_mutex_lock(&lock);
        f1=0;
        pthread_mutex_unlock(&lock);
        printf("Sig1 Red Light on\n");
        sleep(5);
        printf("Sig1 Red Light on\n");
        sleep(5);
        printf("Sig1 Green Light on\n");
        sleep(20);
        printf("Sig1 Yellow Light on\n");
        sleep(5);
        printf("Sig1 Red Light on\n");
        sleep(5);
        i++;
    }

    return 0;

}


//Function that changes light sequence from Green to Red for Signal 2
void *threadFunctionGreentoRedSig2 (void*){


    int i=0;
    while(i<20){
        pthread_mutex_lock(&lock);
        f2=0;
        pthread_mutex_unlock(&lock);
        printf("Sig2 Green Light on\n");
        sleep(20);
        printf("Sig2 Yellow Light on\n");
        sleep(5);
        printf("Sig2 Red Light on\n");
        sleep(5);
        printf("Sig2 Red Light on\n");
        sleep(15);
        pthread_mutex_lock(&lock);
        f2=1;
        pthread_mutex_unlock(&lock);
        sleep(5);
        pthread_mutex_lock(&lock);
        f2=0;
        pthread_mutex_unlock(&lock);
        printf("Sig2 Red Light on\n");
        sleep(5);
        printf("Sig2 Red Light on\n");
        sleep(5);
        i++;
    }

    return 0;

}

//Function that changes light sequence from Red to Green for Signal 2
void *threadFunctionRedtoGreenSig2 (void*){

    int i=0;
    while(i<20){
        pthread_mutex_lock(&lock);
        f2=0;
        pthread_mutex_unlock(&lock);
        printf("Sig2 Red Light on\n");
        sleep(15);
        pthread_mutex_lock(&lock);
 //Flag to check if time remaining is <5s in the normal sequence

        f2=1;
        pthread_mutex_unlock(&lock);
        sleep(5);
        pthread_mutex_lock(&lock);
        f2=0;
        pthread_mutex_unlock(&lock);
        printf("Sig2 Red Light on\n");
        sleep(5);
        printf("Sig2 Red Light on\n");
        sleep(5);
        printf("Sig2 Green Light on\n");
        sleep(20);
        printf("Sig2 Yellow Light on\n");
        sleep(5);
        printf("Sig2 Red Light on\n");
        sleep(5);
        i++;
    }

    return 0;

}


//Function that reads whether the Switch 1 for Signal 1 is pressed or not.
void *threadFunctionReadSwitch1 (void*){

    
    int i=0;
    while(1){
        pthread_mutex_lock(&lock);
        int ff1 = f1;
        pthread_mutex_unlock(&lock);
        char sw1Input;
        scanf("%c", &sw1Input);
        if(sw1Input=='a' && ff1==0){
            
        pthread_mutex_lock(&lock);
        c1=5;
        pthread_mutex_unlock(&lock);
        printf(" switch 1 cliked %d\n", c1);
        }
        c1=0;
        sleep(1);
        i++;
    }

    return 0;

}

//Function that reads whether the Switch 2 for Signal 2 is pressed or not.
void *threadFunctionReadSwitch2 (void*){

    int i=0;
    while(1){
        
        pthread_mutex_lock(&lock);
        int ff2 = f2;
        pthread_mutex_unlock(&lock);
        char sw2Input;
        scanf("%c", &sw2Input);
        
         if(sw2Input=='b' && ff2==0){
            
        pthread_mutex_lock(&lock);
        c2=5;
        pthread_mutex_unlock(&lock);
        printf(" switch 2 cliked %d\n", c2);
            
        }
        
        c2=0;

        sleep(1);
        i++;
    }

    return 0;

}

//Function for thread which reads the counter of switches and check wheteher normal sequence is in last 5 seconds.
//It will switches the threads and restarts the sequence of siganls according to push buttons.
void *threadFunctionReadCount (void*){

    
    int i=0;
    while(1){

        //mutex protection for the shared data which is reading the wait counter
        pthread_mutex_lock(&lock);
        int t1 = c1;
        pthread_mutex_unlock(&lock);
        
        //checks if the wait counter 1 timer is greater than 5 sec, then turns the signal1 to green 
        if(t1>=5){
            pthread_cancel(thread1);
            pthread_cancel(thread4);
            printf("thread start again by S1 \n");
            pthread_create (&thread1, NULL, &threadFunctionGreentoRedSig1, NULL);
            pthread_create (&thread4, NULL, &threadFunctionRedtoGreenSig2, NULL);
            pthread_mutex_lock(&lock);
             c1 = 0;
            pthread_mutex_unlock(&lock);
        }

        //mutex protection for the shared data which is reading the wait counter        
        pthread_mutex_lock(&lock);
        int t2 = c2;
        pthread_mutex_unlock(&lock);
        
        //checks if the wait counter 1 timer is greater than 5 sec, then turns the signal1 to green         
        if(t2>=5 ){
            pthread_cancel(thread1);
            pthread_cancel(thread4);
            printf("thread start again by S2 \n");
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
int main(void)
{
    int del;

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
    
	
	return(0);
}


