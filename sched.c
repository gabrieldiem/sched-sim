#include "sched.h"
#include "switch.h"
#include <limits.h>
#include <stdlib.h>

extern struct proc proc[];

/*
 * Empty selector
 */
struct proc *
select_next_null()
{
	return NULL;
}

/*
 * Selects a random process, it may be not runnable. So there may be idle time
 */
struct proc *
select_next_random()
{
	int n = rand() % NUMPROC;

	if (proc[n].status == RUNNABLE) {
		return &proc[n];
	}

	return NULL;
}

/*
 * Selects a random process that is runnable. Removes idle time from
 * select_next_random. It is kind of a lottery system where the highest ticket
 * (random number) that is runnable is selected
 */
struct proc *
select_next_random_runnable()
{
	int next_random = -1;
	struct proc *next = NULL;

	for (int i = 0; i < NUMPROC; i++) {
		if (proc[i].status == RUNNABLE) {
			int random = rand();
			if (random > next_random) {
				next_random = random;
				next = &proc[i];
			}
		}
	}

	return next;
}

/*
 * Simple fair (meaning to try to give all the processes the same CPU time)
 * selector that selects the process with the smallest runtime
 */
struct proc *
select_next_least_runtime()
{
	int next_runtime = INT_MAX;
	struct proc *next = NULL;

	for (int i = 0; i < NUMPROC; i++) {
		if (proc[i].status == RUNNABLE) {
			if (proc[i].runtime <= next_runtime) {
				next_runtime = proc[i].runtime;
				next = &proc[i];
			}
		}
	}

	return next;
}

void
scheduler()
{
	while (!done()) {
		struct proc *candidate = select_next_least_runtime();

		if (candidate != NULL) {
			candidate->status = RUNNING;
			candidate->runtime += swtch(candidate);
		} else {
			idle();
		}
	}
}