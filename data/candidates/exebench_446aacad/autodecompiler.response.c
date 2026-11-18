int cond_read_lock(struct ref *r)
{
 int ret;

 if (r->count >= 0) {
  r->count++;
  ret = 1;
 } else {
  ret = 0;
 }

 return ret;
}