static struct bytestring *
lookup_bytestring(struct bpf_insn *fp, unsigned char *buf, unsigned int len)
{
 struct bytestring *bp, *new;
 unsigned int h1, h2, h3;

 if (len >= 7) {
  h1 = buf[0] << 8 | buf[1];
  h2 = buf[2] << 8 | buf[3];
  h3 = buf[4] << 8 | buf[5];
 } else if (len >= 5) {
  h1 = buf[0] << 8 | buf[1];
  h2 = buf[2] << 8 | buf[3];
  h3 = 0;
 } else {
  h1 = 0;
  h2 = 0;
  h3 = 0;
 }

 bp = &bytestringtable[h3 & 0xfff];
 while (1) {
  if (bp->next == NULL) {
   bp->h1 = h1;
   bp->h2 = h2;
   bp->h3 = h3;
   bp->string = calloc(1, len + 1);
   if (bp->string == NULL)
    (*fp->error)(fp, "lookup_bytestring: calloc");
   memcpy(bp->string, buf, len);

   bp->next = calloc(1, sizeof(*bp));
   if (bp->next == NULL)
    (*fp->error)(fp, "lookup_bytestring: calloc");

   new = bp;
   break;
  } else if (bp->h1 == h1 && bp->h2 == h2 && bp->h3 == h3 &&
      memcmp(buf, bp->string, len) == 0) {
   new = bp;
   break;
  }
  bp = bp->next;
 }

 return new;
}