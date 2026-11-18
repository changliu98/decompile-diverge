int
match(Reinst *pc, char *sp, char *bol, int flags, Resub *out)
{
 Rune c;
 int i;
 int n;
 Resub scratch;

 for(;;) {
  switch(pc->opcode) {
  default:
   return 0;
  case 1:
   pc = pc->x;
   break;
  case 2:
   memcpy(&scratch, out, sizeof(Resub));
   if(match(pc->x, sp, bol, flags, &scratch)) {
    memcpy(out, &scratch, sizeof(Resub));
    return 1;
   }
   pc = pc->y;
   break;
  case 3:
   if(match(pc->x, sp, bol, flags, out))
    pc = pc->y;
   else
    return 0;
   break;
  case 4:
   memcpy(&scratch, out, sizeof(Resub));
   if(!match(pc->x, sp, bol, flags, &scratch))
    pc = pc->y;
   else
    return 0;
   break;
  case 5:
   sp += chartorune(&c, sp);
   if(c == 0)
    return 0;
   pc++;
   break;
  case 6:
   sp += chartorune(&c, sp);
   if(c == 0 || isnewline(c))
    return 0;
   pc++;
   break;
  case 7:
   sp += chartorune(&c, sp);
   if(c == 0)
    return 0;
   if(flags&0001)
    c = canon(c);
   if(c != pc->c)
    return 0;
   pc++;
   break;
  case 8:
   sp += chartorune(&c, sp);
   if(c == 0)
    return 0;
   if(flags&0001) {
    if(!incclasscanon(pc->cc, canon(c)))
     return 0;
   } else {
    if(!incclass(pc->cc, c))
     return 0;
   }
   pc++;
   break;
  case 9:
   sp += chartorune(&c, sp);
   if(c == 0)
    return 0;
   if(flags&0001) {
    if(incclasscanon(pc->cc, canon(c)))
     return 0;
   } else {
    if(incclass(pc->cc, c))
     return 0;
   }
   pc++;
   break;
  case 10:
   n = out->sub[pc->n].ep - out->sub[pc->n].sp;
   if(flags&0001) {
    if(strncmpcanon(sp, out->sub[pc->n].sp, n) != 0)
     return 0;
   } else {
    if(strncmp(sp, out->sub[pc->n].sp, n) != 0)
     return 0;
   }
   if(n > 0)
    sp += n;
   pc++;
   break;
  case 11:
   if(sp == bol && !(flags&0004)) {
    pc++;
    break;
   }
   if(!(flags&0002) || sp <= bol || !isnewline(sp[-1]))
    return 0;
   pc++;
   break;
  case 12:
   if(*sp == '\0') {
    pc++;
    break;
   }
   if(!(flags&0002) || !isnewline(*sp))
    return 0;
   pc++;
   break;
  case 13:
   i = 0;
   if(sp > bol && iswordchar(sp[-1]))
    i = 1;
   if(iswordchar(*sp) == i)
    return 0;
   pc++;
   break;
  case 14:
   i = 0;
   if(sp > bol && iswordchar(sp[-1]))
    i = 1;
   if(iswordchar(*sp) != i)
    return 0;
   pc++;
   break;
  case 15:
   out->sub[pc->n].sp = sp;
   pc++;
   break;
  case 16:
   out->sub[pc->n].ep = sp;
   pc++;
   break;
  case 0:
   return 1;
  }
 }
}