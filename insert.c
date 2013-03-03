#include <xinu.h>

/* insert a process into a queue in descending key order */
status insert(pid32 pid, qid16 q, int32 key) {
  int16 curr, prev;
  if (isbadqid(q) || isbadpid(pid)) {
    return SYSERR;
  }
  curr = firstid(q);
  while (queuetab[curr].qkey >= key) {
    curr = queuetab[curr].qnext;
  }
  prev = queuetab[curr].qprev;
  queuetab[pid].qnext = curr;
  queuetab[pid].qprev = prev;
  queuetab[pid].qkey = key;
  queuetab[prev].qnext = pid;
  queuetab[curr].qprev = pid;
  return OK;
}
