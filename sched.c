#include "sched.h"
#include "switch.h"
#include <limits.h>
#include <stdlib.h>

extern struct proc proc[];

// Empty selector
struct proc *select_next_null() { return NULL; }

// Selects a random process, it may be not runnable. So there may be idle time
struct proc *select_next_random() {
  int n = rand() % NUMPROC;

  if (proc[n].status == RUNNABLE) {
    return &proc[n];
  }

  return NULL;
}

// Selects a random process that is runnable. Removes idle time from select_next_random
struct proc *select_next_random_runnable() {
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

void scheduler() {
  while (!done()) {
    struct proc *candidate = select_next_random_runnable();

    if (candidate != NULL) {
      candidate->status = RUNNING;
      candidate->runtime += swtch(candidate);
    } else {
      idle();
    }
  }
}