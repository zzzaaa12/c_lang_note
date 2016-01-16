/*
Reference:
	1. http://dragonspring.pixnet.net/blog/post/32963482
	2. http://fanqiang.chinaunix.net/a4/b8/20010811/0905001105_b.html
	3. http://sp1.wikidot.com/pthread
	4. https://computing.llnl.gov/tutorials/pthreads/
*/

#include <stdio.h>
#include <pthread.h>

void* thread0(void*);
void* thread1(void*);

int main(void) {

	void* result;
	pthread_t t0; 
	pthread_t t1; 

	pthread_create(&t0, NULL, thread0, NULL);
	pthread_create(&t1, NULL, thread1, NULL);

	/* wait for thread terminate */
	pthread_join(t0, &result);
	pthread_join(t1, &result);

	return 0;
}

void* thread0(void *argu)
{
	int i = 0;
	for (; i<5; i++) {
		printf("thread0: %d\n", i); 
		sleep(1);
	}   
	return NULL;
}


void* thread1(void *argu)
{
	int i = 0;
	for (; i<10; i++) {
		printf("thread1: %d\n", i); 
		sleep(1);
	}   
	return NULL;
}
