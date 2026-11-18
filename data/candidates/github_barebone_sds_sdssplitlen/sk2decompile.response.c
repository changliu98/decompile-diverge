sds *sdssplitlen(const char *s, ssize_t len, const char *sep, int seplen,
                 int *count) {
  sds *tokens, *newtokens;
  long i, start, tokens_alloc;
  int j, tokens_count;
  tokens_count = 0;
  tokens_alloc = 5;
  start = 0;
  if (seplen < 1 || len <= 0) {
    *count = 0;
    return NULL;
  }
  tokens = malloc(sizeof(sds) * tokens_alloc);
  if (tokens == NULL) return NULL;
  for (i = 0; i < (len - (seplen - 1)); i++) {
    if (tokens_alloc < tokens_count + 2) {
      tokens_alloc *= 2;
      newtokens = realloc(tokens, sizeof(sds) * tokens_alloc);
      if (newtokens == NULL) goto cleanup;
      tokens = newtokens;
    }
    if ((seplen == 1 && s[i] == sep[0]) || !memcmp(s + i, sep, seplen)) {
      tokens[tokens_count] = sdsnewlen(s + start, i - start);
      if (tokens[tokens_count] == NULL) goto cleanup;
      tokens_count++;
      start = i + seplen;
      i = start - 1;
    }
  }
  tokens[tokens_count] = sdsnewlen(s + start, len - start);
  if (tokens[tokens_count] == NULL) goto cleanup;
  tokens_count++;
  *count = tokens_count;
  return tokens;
cleanup : {
  int jj;
  for (jj = 0; jj < tokens_count; jj++) sdsfree(tokens[jj]);
  free(tokens);
  *count = 0;
  return NULL;
}
}