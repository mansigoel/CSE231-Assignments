#include<stdio.h>
#include<pthread.h>
#include<assert.h>
#include<semaphore.h>
//run using gcc -lpthread 14105_mtp_c1.c 
#define MAX 1000000000
sem_t m;
static volatile long long int count=0;
void *increment(void *c)
{
	int i;
	for(i=0;i< MAX;i++)
		{
			sem_wait(&m);
			if(count<MAX)		
					count++;
			sem_post(&m);
				
		}
	return NULL;
}
int main(int argc, char *argv[])
{
	int i,j;
	for(i=2;i<=10;i++)
	{
		pthread_t t1[i+1];
        int counter=0;

		sem_init(&m, 0, 1);
        double total_time=0;
        while(counter<50)
        {
	        //printf("%d\n",counter);
	        count = 0;
	        clock_t start, end;
	        double cpu_time_used;
		 	start = clock();
		 	int rc;
		 	for( j=0;j<i;j++)
		 	{
		    	rc=pthread_create(&t1[j], NULL, increment, NULL);
		    	assert(rc==0);
		    }
		    for(j=0;j<i;j++)
		 	{
		    	rc = pthread_join(t1[j], 0);
		    	assert(rc == 0);
		    }
		    end = clock();
		    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		   	total_time+=cpu_time_used;
		    counter++;
		}
		printf("time taken %lf by %d threads\n",total_time/50, i);
		printf("counter value is :%lld\n",count);
	}
    return  0;
}

