int try_enlarge(RespResponse *r,uint32_t add_size)

{
  char *pcVar1;
  char *more_buf;
  uint32_t new_size;
  uint32_t add_size_local;
  RespResponse *r_local;
  int local_c;
  
  for (new_size = r->buf_size; new_size < r->used_size + add_size; new_size = new_size << 1) {
  }
  pcVar1 = realloc(r->buf,(ulong)new_size);
  if (pcVar1 == (char *)0x0) {
    local_c = -1;
  }
  else {
    r->buf = pcVar1;
    r->buf_size = new_size;
    local_c = 0;
  }
  return local_c;
}