void
endrun(struct state *sp)
{
 sp->len--;
 literal(sp, sp->lit);
 if (sp->len >= 68) {
  encodelen(sp, 277, 4, sp->len - 68);
  return;
 }
 if (sp->len >= 36) {
  encodelen(sp, 273, 3, sp->len - 36);
  return;
 }
 if (sp->len >= 20) {
  encodelen(sp, 269, 2, sp->len - 20);
  return;
 }
 if (sp->len >= 12) {
  encodelen(sp, 265, 1, sp->len - 12);
  return;
 }
 if (sp->len >= 4) {
  encodelen(sp, 257, 0, sp->len - 4);
  return;
 }

 while (sp->len--)
  literal(sp, sp->lit);
}