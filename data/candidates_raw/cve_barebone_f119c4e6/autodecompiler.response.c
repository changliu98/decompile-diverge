static int _dns_encode_HTTPS(struct dns *d, struct dns_HTTPS *r)
{
 int ret = 0;
 char name[256];
 unsigned int type = 0, class = 0;
 unsigned int rr_len = 0, rr_start = 0, ttl = 0, priority = 0;
 unsigned short left = sizeof(name);
 unsigned char *p = NULL;

 memset(name, 0, sizeof(name));
 rr_len = 0;
 rr_start = 0;
 ttl = 0;
 priority = 0;

 p = dns_get_HTTPS_svcparm_start(r, name, sizeof(name), &ttl, &priority);
 if (!p) {
  do { tlog_ext(4, "harness.c", 694, "_dns_encode_HTTPS", NULL, "get https param failed."); } while (0);
  return -1;
 }

 ret = _dns_encode_rr_head(d, name, type, class, ttl, &rr_len);
 if (ret < 0)
  return -1;

 rr_start = ((d)->cursor.p - (d)->cursor.b);

 if (_dns_left_len(d) < 3) {
  do { tlog_ext(4, "harness.c", 705, "_dns_encode_HTTPS", NULL, "left len is invalid."); } while (0);
  return -1;
 }
 _dns_write_short(&d->cursor, priority);

 ret = _dns_encode_domain(d, name);
 if (ret < 0)
  return -1;

 rr_start = ((d)->cursor.p - (d)->cursor.b);

 while (p) {
  if (((d)->cursor.p - (d)->cursor.b) > r->len || _dns_left_len(d) < 1)
   return -1;

  _dns_write_short(&d->cursor, ((unsigned short *)p)[0]);
  _dns_write_short(&d->cursor, ((unsigned short *)p)[1]);

  switch (((unsigned short *)p)[0]) {
  case 0x0000:
  case 0x0001:
  case 0x0002:
  case 0x0003:
  case 0x0004:
  case 0x0005:
  case 0x0006:
   memcpy(d->cursor.p, p + 4, ((unsigned short *)p)[1]);
   d->cursor.p += ((unsigned short *)p)[1];
   break;
  default:
   d->cursor.p -= 4;
   break;
  }

  p = dns_get_HTTPS_svcparm_next(r, p);
 }

 _dns_write_short(&rr_len, ((d)->cursor.p - (d)->cursor.b) - rr_start);

 return 0;
}