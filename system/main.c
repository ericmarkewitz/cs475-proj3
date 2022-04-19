/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5	//number of philosophers and forks

//TODO - locks must be declared and initialized here
mutex_t **forks;
mutex_t* outputPrinter = FALSE;


/**
 * Delay for a random amount of time
 * @param alpha delay factor
 */
void	holdup(int32 alpha)
{
	long delay = rand() * alpha;
	while (delay-- > 0)
		;	//no op
}

/**
 * Eat for a random amount of time
 */
void	eat()
{
	holdup(10000);
}

/**
 * Think for a random amount of time
 */
void	think()
{
	holdup(1000);
}



/**
 * Philosopher's code
 * @param phil_id philosopher's id
 */
void	philosopher(uint32 phil_id)
{
	//TODO - right fork
	uint32 right;
	if(phil_id == 0) {
		right = forks[N-1];
	}
	else {
		right = forks[phil_id-1];
	}				
	uint32 left = forks[phil_id];	//TODO - left fork
	srand(phil_id);
	while (TRUE)
	{
		//TODO
		//think 70% of the time
		//eat 30% of the time
		int random = rand() % 100;
		mutex_lock(&outputPrinter);
		kprintf("random: %d\n", random);
		mutex_unlock(&outputPrinter);
		if(random < 30) {
			if(right == 0) {
				mutex_lock(&right);
				if(left == 0) {
					mutex_lock(&left);
					mutex_lock(&outputPrinter);
					kprintf("Philosopher %d eating: nom nom nom\n", phil_id);
					eat();
					mutex_unlock(&outputPrinter);
					mutex_unlock(&left);
					mutex_unlock(&right);
				}
				else {
					mutex_unlock(&right);
					mutex_lock(&outputPrinter);
					kprintf("Philosopher %d thinking: zzzzzZZZz\n", phil_id);
					think();
					mutex_unlock(&outputPrinter);
				}
			}
			else {
				mutex_lock(&outputPrinter);
				kprintf("Philosopher %d thinking: zzzzzZZZz\n", phil_id);
				think();
				mutex_unlock(&outputPrinter);
			}
		}
		else {
			mutex_lock(&outputPrinter);
			kprintf("Philosopher %d thinking: zzzzzZZZz\n", phil_id);
			think();
			mutex_unlock(&outputPrinter);
		}
	}
}

int	main(uint32 argc, uint32 *argv)
{
	forks = (mutex_t **) malloc(sizeof(mutex_t *) * N);
	int i;
	for(i = 0; i < N; i++) {
		mutex_t *lock = (mutex_t *) malloc(sizeof(mutex_t *));
	}
	//do not change
	ready(create((void*) philosopher, INITSTK, 15, "Ph1", 1, 0), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph2", 1, 1), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph3", 1, 2), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph4", 1, 3), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph5", 1, 4), FALSE);

	for(i = 0; i < N; i++) {
		free(sizeof(mutex_t*), forks[i]);
	}
	free(sizeof(mutex_t*) * N, forks);
	free(sizeof(mutex_t*), outputPrinter);

	return 0;
}
