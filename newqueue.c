#include <xinu.h>

/* allocate and initialize a queue in the global queue table */
qid16 newqueue(void) {
  static qid16 nextqid = NPROC;
  qid16 q = nextqid;
  if (q > NQENT) {
    return SYSERR;
  }
  nextqid += 2;

  struct qentry *queuehdentry = &queuetab[queuehead(q)];
  struct qentry *queuetlentry = &queuetab[queuetail(q)];
  /* head init */
  queuehdentry->qnext = queuetail(q);
  queuehdentry->qprev = EMPTY;
  queuehdentry->qkey = MAXKEY;
  /* tail init */
  queuetlentry->qnext = EMPTY;
  queuetlentry->qprev = queuehead(q);
  queuetlentry->qkey = MINKEY;

  return q;
}
