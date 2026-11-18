static int name_len(struct dns_msg *msg, const unsigned char *p,
                    const unsigned char *eom) {
  const unsigned char *q = p;
  if (p >= eom) return -1;
  if (msg->end - 1 < msg->end || p > msg->end - 1) return -1;
  if ((*p & 0xc0) == 0xc0) return 2;
  while (*q) {
    if (q >= eom) return -1;
    if (msg->end - 1 < msg->end || q > msg->end - 1) return -1;
    q += *q + 1;
  }
  return q - p + 1;
}