/* Raghad qadah-1170142
   Shaymaa zaid-1170540
   Leena Bany Odeh-1172351


*/




#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
int count1=0;
int count2=0;
int count=0;
int pid=0;
int num1=0;
int num2=0;
int p1,p2;
int flag=0;
int i=1;

int main(void)
{
    pid=getpid();

    void signal_catcherP1(int);
    void signal_catcherP2(int);
    void signal_catcherpid(int);
    void signal_catcherq(int);
    p1= fork();

    if(p1==0) //child 1
    {

        // P1 will be sensitive to signal SIGUSR1
        if ( sigset(SIGUSR1, signal_catcherP1) == -1 )
        {
            perror("Sigset can not set SIGUSR1");
            exit(SIGUSR1);
        }
        while(1);

    }
    else  //child2
    {

        p2=fork();

        if(p2==0)
        {

            //P2 will be sensitive to signal SIGUSR1
            if ( sigset(SIGUSR1, signal_catcherP2) == -1 )
            {
                perror("Sigset can not set SIGUSR1");
                exit(SIGUSR1);
            }
            while(1);

        }

        else  //parent
        {

            
            //parent process will be sensitive to both signals SIGINT and SIGQUIT

            if ( sigset(SIGINT, signal_catcherpid) == -1 )
            {
                perror("Sigset can not set SIGINT");
                exit(SIGINT);
            }

            if ( sigset(SIGQUIT, signal_catcherq) == -1 )
            {
                perror("Sigset can not set SIGQUIT");
                exit(SIGQUIT);
            }

            sleep(1);
            //parent process will ask P1 and P2 to pick a random integer number
            kill(p1,SIGUSR1);
            kill(p2,SIGUSR1);
            while(1);

        }

    }
}

void signal_catcherP1(int the_sig)
{
    //P1 will write its picked number in the file P1.txt
    srand(time(0)+getpid());
    int y=rand()%100;
    printf ("P1--> random =%d\n",y);
    FILE *fptr1=fopen("p1.txt","w");
    fprintf(fptr1,"%d\n",y);
    fclose(fptr1);
    //after finish writing numbers,informs the parent process
    kill(pid,2);
    }
void signal_catcherP2(int the_sig)
{
    //P2 will write its picked number in the file P2.txt
    srand(time(0));
    FILE *fptr2=fopen("p2.txt","w");
    int x=rand()%100;
    fprintf(fptr2,"%d\n",x);
    printf ("P2--> random =%d\n",x);
    fclose(fptr2);


    //after finish writing numbers,informs the parent process
    sleep(1);
    kill(pid,2);

}


void signal_catcherq(int the_sig)
{

    printf("\nSIGQUIT signal recived ");
    exit(1);
}

void signal_catcherpid(int the_sig)
{

    //the parent process will read the picked number in file p1.txt 

    // sleep(2);
    if (flag==0){
        FILE *f1=fopen("p1.txt","r");
        fscanf(f1,"%d",&num1);
        fclose(f1);
        flag=1;
    }
    //the parent process will read the picked number in file p2.txt
    else{
       sleep (1);
       FILE *f2=fopen("p2.txt","r");
       fscanf(f2,"%d",&num2);
       fclose(f2);

   
    //comparing the numbers picked by P1 and P2 to declares the round winner
    if (num1>num2)
    {
        count1++;
    }
    else if (num1<num2)
    {
        count2++;
    }
    else
    {
        count1++;
        count2++;
    }
    printf("count1 = %d ",count1);
    printf("count2 = %d ",count2);
    printf("\n");

    //by the ends of current round he parent process deletes the files P1.txt and P2.txt.
    if (remove("p1.txt") == 0)
       printf("Deleted p1 file successfully \n");
    if (remove("p2.txt") == 0)
        printf("Deleted p2 file successfully");
        printf("\n>>>>>>>>>>>>> Round %d ends",i);
               printf("<<<<<<<<<<<<<");
           printf("\n\n");
            i++;

    /*
     continue unless the counter of either P1 or P2 has reached 10.
      The parent process declares the winner of the game then kills P1 and P2 and exits
    */
    if((count1 >=10) || (count2>=10))
    {
        if (count1>count2)
        {
            printf("P1 Wins \n");
            kill(p1,SIGKILL);
            kill(p2,SIGKILL);
            exit(0);
        }
        else if (count1<count2)
        {
            printf("P2 Wins\n ");
            kill(p1,SIGKILL);
            kill(p2,SIGKILL);
            exit(0);
        }
        else
        {
            printf("All Wins \n ");
            kill(p1,SIGKILL);
            kill(p2,SIGKILL);
            exit(0);
        }
    }
    flag=0;
    kill(p1,SIGUSR1);
    kill(p2,SIGUSR1);
}
}
