int sample_conv_regsub(sample_t *sample, sample_conv_t *conv, void *arg) {
  regex_t *re = sample->re.ptr;
  chunk_t *chunk = get_trash_chunk();
  char *s = conv->in.str.data;
  char *e = s + conv->in.str.len;
  int flags = 0;
  chunk_t *chunk2;
  regmatch_t pmatch[10];
  int r;
  int len;
  for (;;) {
    r = 0;
    if (!(sample->flags & 0x00000002) && (flags & 0x00000001)) {
    } else {
      r = regex_exec_match2(re, s, e - s, 10, pmatch, flags);
    }
    if (!r) {
      pmatch[0].rm_eo = e - s;
    }
    len = chunk->size - chunk->len;
    if (len && pmatch[0].rm_eo > 0) {
      if (len > pmatch[0].rm_eo) {
        len = pmatch[0].rm_eo;
      }
      memcpy(chunk->data + chunk->len, s, len);
      chunk->len += len;
    }
    if (!r) {
      break;
    }
    chunk2 = alloc_trash_chunk();
    if (!chunk2) {
      break;
    }
    chunk2->len = exp_replace(chunk2->data, chunk2->size, s,
                              sample->exp.regsub.data, pmatch);
    len = chunk2->size - chunk2->len;
    if (len) {
      if (len > chunk2->len) {
        len = chunk2->len;
      }
      memcpy(chunk->data + chunk->len, chunk2->data, len);
      chunk->len += len;
    }
    free_trash_chunk(chunk2);
    if (s >= e) {
      break;
    }
    if (pmatch[0].rm_so == 0) {
      if (chunk->len < chunk->size) {
        chunk->data[chunk->len++] = s[pmatch[0].rm_so];
      }
      pmatch[0].rm_so++;
    }
    s += pmatch[0].rm_so;
    flags |= 0x00000001;
  }
  conv->in = *chunk;
  return 1;
}