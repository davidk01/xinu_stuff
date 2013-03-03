/* queue.h - firstid, firstkey, isempty, lastkey, nonempty */
#ifndef NQENT
#define NQENT (NPROC + 4 + NSEM + NSEM)
#endif

#define EMPTY (-1)
#define MAXKEY 0x7FFFFFFF
#define MINKEY 0x80000000

struct qentry {
  int32 qkey;
  qid16 qnext;
  qid16 qprev;
};

extern struct qentry queuetab[];

#define queuehead(q) (q)
#define queuetail(q) ((q) + 1)
#define firstid(q) (queuetab[queuehead(q)].qnext)
#define lastid(q) (queuetab[queuetail(q)].qprev)
#define isempty(q) (firstid(q) >= NPROC)
#define nonempty(q) (firstid(q) < NPROC)
#define firstkey(q) (queuetab[firstid(q)].qkey)
#define lastkey(q) (queuetab[lastid(q)].qkey)

/* Inline to check queue id assumes interrupts are disabled */
#define isbadqid(x) (((int32)(x) < 0) || (int32)(x) >= NQENT-1)

/* Queue function prototypes */
pid32 getfirst(qid16);
pid32 getlast(qid16);
pid32 getitem(pid32);
pid32 enqueue(pid32, qid16);
pid32 dequeue(qid16);
status insert(pid32, qid16, int);
status insertd(pid32, qid16, int);
qid16 newqueue(void);
