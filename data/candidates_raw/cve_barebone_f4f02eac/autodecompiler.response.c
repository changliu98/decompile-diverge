static int match(uchar *code, char *sp, char *bol, int flags, Resub *sub)
{
 int c;
 int n;
 Rune r;
 Resub subtmp;

loop:
 switch(*code++) {
 default:
  abort__bench();
  break;
 case 0:
  return 1;
 case 1:
  code = ((uchar**)code)[0];
  goto loop;
 case 2:
  memcpy(&subtmp, sub, sizeof(subtmp));
  if(match(((uchar**)code)[0], sp, bol, flags, &subtmp)){
   memcpy(sub, &subtmp, sizeof(subtmp));
   return 1;
  }
  code = ((uchar**)code)[1];
  goto loop;
 case 3:
  if(!match(((uchar**)code)[0], sp, bol, flags, sub))
   return 0;
  code = ((uchar**)code)[1];
  goto loop;
 case 4:
  memcpy(&subtmp, sub, sizeof(subtmp));
  if(match(((uchar**)code)[0], sp, bol, flags, &subtmp)){
   return 0;
  }
  code = ((uchar**)code)[1];
  goto loop;
 case 5:
  sp += chartorune(&r, sp);
  if(r == 0)
   return 0;
  code += 2*sizeof(int);
  goto loop;
 case 6:
  sp += chartorune(&r, sp);
  if(r == 0)
   return 0;
  if(isnewline(r))
   return 0;
  code += 2*sizeof(int);
  goto loop;
 case 7:
  sp += chartorune(&r, sp);
  if(r == 0)
   return 0;
  if(flags & 1)
   r = canon(r);
  if(r != ((int*)code)[1])
   return 0;
  code += 2*sizeof(int);
  goto loop;
 case 8:
  sp += chartorune(&r, sp);
  if(r == 0)
   return 0;
  if(flags & 1){
   if(!incclasscanon(((Cc*)code)->c, canon(r)))
    return 0;
  }else{
   if(!incclass(((Cc*)code)->c, r))
    return 0;
  }
  code += 2*sizeof(int);
  goto loop;
 case 9:
  sp += chartorune(&r, sp);
  if(r == 0)
   return 0;
  if(flags & 1){
   if(incclasscanon(((Cc*)code)->c, canon(r)))
    return 0;
  }else{
   if(incclass(((Cc*)code)->c, r))
    return 0;
  }
  code += 2*sizeof(int);
  goto loop;
 case 10:
  n = ((int*)sub)[((uchar)code[1])*2+1] - ((int*)sub)[((uchar)code[1])*2];
  if(flags & 1){
   if(strncmpcanon(sp, ((int*)sub)[((uchar)code[1])*2], n) != 0)
    return 0;
  }else{
   if(strncmp(sp, ((int*)sub)[((uchar)code[1])*2], n) != 0)
    return 0;
  }
  if(n > 0)
   sp += n;
  code += 2*sizeof(int);
  goto loop;
 case 11:
  if(sp == bol && !(flags & 4))
   goto loop;
  if(flags & 2){
   if(sp > bol && isnewline(sp[-1]))
    goto loop;
  }
  return 0;
 case 12:
  if(*sp == 0)
   goto loop;
  if(flags & 2){
   if(isnewline(*sp))
    goto loop;
  }
  return 0;
 case 13:
  n = (sp > bol && iswordchar(sp[-1])) ? 1 : 0;
  n ^= iswordchar(*sp);
  if(n == 0)
   return 0;
  goto loop;
 case 14:
  n = (sp > bol && iswordchar(sp[-1])) ? 1 : 0;
  n ^= iswordchar(*sp);
  if(n != 0)
   return 0;
  goto loop;
 case 15:
  ((int*)sub)[((uchar)code[1])*2] = (int)sp;
  code += 2*sizeof(int);
  goto loop;
 case 16:
  ((int*)sub)[((uchar)code[1])*2+1] = (int)sp;
  code += 2*sizeof(int);
  goto loop;
 }
 return 0;
}