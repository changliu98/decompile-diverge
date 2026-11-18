int pqueue_insert(pqueue_t *q, void *d) {
 size_t newsize;
 void **newd;

 if (!q)
  return 1;

 if (q->size >= q->avail) {
  newsize = q->size + q->step;
  newd = realloc(q->d, newsize * sizeof(void *));
  if (!newd)
   return 1;
  q->d = newd;
  q->avail = newsize;
 }

 q->d[q->size++] = d;
 bubble_up(q, q->size - 1);

 return 0;
}