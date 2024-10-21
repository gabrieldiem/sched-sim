#ifndef SCHED_H
#define SCHED_H

#define NUMPROC 5
#define TIMESLICE 20

enum Status { RUNNING, RUNNABLE, BLOCKED };

struct proc {
	int pid;
	enum Status status;

	int runtime;
};

void scheduler();

#endif