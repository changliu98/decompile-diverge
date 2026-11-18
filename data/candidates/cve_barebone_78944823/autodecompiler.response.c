static int sample_conv_regsub(struct edna *a, struct line *b, char *c)
{
 struct trash *t, *t2;
 regmatch_t rm[10];
 int i, j, k, l, m, n, o, p, q, r, s, u, v, w, x, y, z;

 t = a->trash;
 t2 = get_trash_chunk();
 char *ptr = b->data, *end = ptr + b->len;
 int flags = 0;

 while (1) {
  int match = 0;
  if ((a->flags & 2) || !(flags & 1))
   match = regex_exec_match2(&a->regex, ptr, end - ptr, 10, rm, flags);

  if (!match) rm[0].rm_so = end - ptr;

  if ((k = t2->alloc - t2->len) && rm[0].rm_so > 0) {
   if (k > rm[0].rm_so) k = rm[0].rm_so;
   memcpy(t2->data + t2->len, ptr, k);
   t2->len += k;
  }

  if (!match) break;

  t2 = alloc_trash_chunk();
  if (!t2) break;

  t2->len = exp_replace(t2->data, t2->alloc, ptr, a->subst, rm);
  if ((k = t2->alloc - t2->len)) {
   if (k > t2->len) k = t2->len;
   memcpy(t->data + t->len, t2->data, k);
   t->len += k;
  }
  free_trash_chunk(t2);

  if (ptr >= end) break;
  if (!rm[0].rm_eo) {
   if (t->len < t->alloc) t->data[t->len++] = ptr[rm[0].rm_eo];
   rm[0].rm_eo++;
  }
  ptr += rm[0].rm_eo;
  flags |= 1;
 }

 b->alloc = t2->alloc;
 b->data = t2->data;
 b->len = t2->len;
 b->pos = t2->pos;

 return 1;
}