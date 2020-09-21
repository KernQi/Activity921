#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t chopstick[5];

void* think_eat_sleep(void* argument) {
	// n: philosopher number
	int n = *((int*) (argument));

	while(1) {
		printf ("Philosopher %d is thinking\n", n);

		pthread_mutex_lock(&chopstick[n]);
		//usleep(rand() % 1000000);
		pthread_mutex_lock(&chopstick[(n+1) % 5]);

		printf ("Philosopher %d got hungry. Eating...\n", n);

		usleep(100000); //time in miliseconds

		pthread_mutex_unlock(&chopstick[n]);
		pthread_mutex_unlock(&chopstick[(n+1) % 5]);

		printf ("Philosopher %d is full. Sleeping zzz...\n", n);

		// Nap for up to a second
		usleep(rand() % 1000000);
	}
	return NULL;
}

int main(int argc, char** argv) {
	pthread_t thread_IDs[5];
	int philosophers[5];

	for(int i = 0; i < 5; i++) {
		pthread_mutex_init(&chopstick[i], NULL);
	}

	for(int i = 0; i < 5; i++) {
		philosophers[i] = i;
		pthread_create(&thread_IDs[i], NULL, think_eat_sleep, (void*) (philosophers+i));
	}

	for(int i = 0; i < 5; i++) {
		pthread_join(thread_IDs[i], NULL);
	}

	for(int i = 0; i < 5; i++) {
		pthread_mutex_destroy(&chopstick[i]);
	}

	return 0;
}
