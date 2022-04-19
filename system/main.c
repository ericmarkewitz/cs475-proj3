/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5	//number of philosophers and forks

//TODO - locks must be declared and initialized here
// mutex_t** forks;
// mutex_t* outputPrinter = FALSE;
mutex_t outputPrinter = FALSE;
mutex_t forks[N] = {FALSE, FALSE, FALSE, FALSE, FALSE};
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
		right = N-1;
	}
	else {
		right = phil_id-1;
	}				
	uint32 left = phil_id;	//TODO - left fork
	mutex_lock(&outputPrinter);
	kprintf("phil_id: %d, right: %d, left: %d\n", phil_id, right, left);
	mutex_unlock(&outputPrinter);
	int i;
	srand(phil_id);
	while (TRUE)
	{
		//TODO
		//think 70% of the time
		//eat 30% of the time
		
		int random = rand() % 100;
		if(random < 30) {
			mutex_lock(&forks[right]);
			if(!forks[left]) { //if (!fork[left])
				mutex_lock(&forks[left]);
				mutex_lock(&outputPrinter);
				kprintf("Philosopher %d eating: nom nom nom\n", phil_id);
				mutex_unlock(&outputPrinter);
				eat();
				mutex_unlock(&forks[left]);
				mutex_unlock(&forks[right]);
			}
			else {
				mutex_unlock(&forks[right]);
			}
		}
		else {
			mutex_lock(&outputPrinter);
			kprintf("Philosopher %d thinking: zzzzzZZZz\n", phil_id);
			mutex_unlock(&outputPrinter);
			think();
		}
	}
}

int	main(uint32 argc, uint32 *argv)
{
	//do not change
	ready(create((void*) philosopher, INITSTK, 15, "Ph1", 1, 0), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph2", 1, 1), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph3", 1, 2), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph4", 1, 3), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph5", 1, 4), FALSE);

	return 0;
}