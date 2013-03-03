/* getitem.c - getfirst, getlast, getitem */
#include <xinu.h>

/* remove a process from the front of a queue */
pid32 getfirst(qid16 q) {
  pid32 head;
  if (isempty(q)) {
    return EMPTY;
  }
  head = queuehead(q);
  return getitem(queuetab[head].qnext);
}

/* remove a process from the end of a queue */
pid32 getlast(qid16 q) {
  pid32 tail;
  if (isempty(q)) {
    return EMPTY;
  }
  tail = queuetail(q);
  return getitem(queuetab[tail].qprev);
}

/* remove a process from an arbitrary point in a queue */
pid32 getitem(pid32 pid) {
  pid32 prev, next;
  next = queuetab[pid].qnext;
  prev = queuetab[pid].qprev;
  queuetab[prev].qnext = next;
  queuetab[next].qprev = prev;
  return pid;
}
