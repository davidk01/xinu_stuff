#include <xinu.h>

struct qentry queuetab[NQENT];

/* insert a process at the tail of a queue */
pid32 enqueue(pid32 pid, qid16 q) {
  int tail, prev;
  if (isbadqid(q) || isbadpid(pid)) {
    return SYSERR;
  }
  tail = queuetail(q);
  prev = queuetab[tail].qprev;
  queuetab[pid].qnext = tail;
  queuetab[pid].qprev = prev;
  queuetab[prev].qnext = pid;
  queuetab[tail].qprev = pid;
  return pid;
}

/* remove and return the first process on a list */
pid32 dequeue(qid16 q) {
  pid32 pid;
  if (isbadqid(q)) {
    return SYSERR;
  } else if (isempty(q)) {
    return EMPTY;
  }
  pid = getfirst(q);
  queuetab[pid].qprev = EMPTY;
  queuetab[pid].qnext = EMPTY;
  return pid;
}
