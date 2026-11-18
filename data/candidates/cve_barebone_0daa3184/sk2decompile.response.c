static struct bytestring_hash *lookup_bytestring(serd_env *env,
                                                 const unsigned char *str,
                                                 int len) {
  struct bytestring_hash *h;
  int h0, h1, h2;
  if (len >= 6) {
    h0 = (str[0] << 8) | str[1];
    h1 = (str[2] << 8) | str[3];
    h2 = (str[4] << 8) | str[5];
  } else if (len >= 4) {
    h0 = (str[0] << 8) | str[1];
    h1 = (str[2] << 8) | str[3];
    h2 = 0;
  } else {
    h0 = 0;
    h1 = 0;
    h2 = 0;
  }
  for (h = &bytestring_hash_table[(h1 ^ h2) & 0xfff]; h->next; h = h->next) {
    if (h->h2 == h2 && h->h1 == h1 && h->h0 == h0 && !memcmp(str, h->str, len))
      return h;
  }
  h->h2 = h2;
  h->h1 = h1;
  h->h0 = h0;
  h->str = calloc(1, len + 1);
  if (h->str == NULL) env->error(env, "lookup_bytestring: calloc");
  memcpy(h->str, str, len);
  h->next = calloc(1, sizeof(*h));
  if (h->next == NULL) env->error(env, "lookup_bytestring: calloc");
  return h;
}