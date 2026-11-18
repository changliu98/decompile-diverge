int
evbuffer_unfreeze(struct evbuffer *buffer, int start)
{
 int res = 0;
 do { do { if ((buffer)->lock) _evthread_lock_fns.lock(0, (buffer)->lock); } while (0); } while (0);
 if (buffer->freeze_start > start) {
  buffer->freeze_start = start;
  res = 1;
 }
 do { do { if ((buffer)->lock) _evthread_lock_fns.unlock(0, (buffer)->lock); } while (0); } while (0);
 return res;
}