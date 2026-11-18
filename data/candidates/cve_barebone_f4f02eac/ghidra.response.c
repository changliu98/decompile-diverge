int match(Reinst *pc,char *sp,char *bol,int flags,Resub *out)

{
  Reclass *pRVar1;
  uint uVar2;
  int iVar3;
  bool local_102;
  bool local_101;
  Rune c;
  int i;
  Resub scratch;
  Resub *out_local;
  int flags_local;
  char *bol_local;
  char *sp_local;
  Reinst *pc_local;
  
  sp_local = sp;
  pc_local = pc;
  do {
    switch(pc_local->opcode) {
    case '\0':
      return 1;
    case '\x01':
      pc_local = pc_local->x;
      break;
    case '\x02':
      memcpy(&scratch,out,0xa8);
      iVar3 = match(pc_local->x,sp_local,bol,flags,&scratch);
      if (iVar3 != 0) {
        memcpy(out,&scratch,0xa8);
        return 1;
      }
      pc_local = pc_local->y;
      break;
    case '\x03':
      iVar3 = match(pc_local->x,sp_local,bol,flags,out);
      if (iVar3 == 0) {
        return 0;
      }
      pc_local = pc_local->y;
      break;
    case '\x04':
      memcpy(&scratch,out,0xa8);
      iVar3 = match(pc_local->x,sp_local,bol,flags,&scratch);
      if (iVar3 != 0) {
        return 0;
      }
      pc_local = pc_local->y;
      break;
    case '\x05':
      iVar3 = chartorune(&c,sp_local);
      sp_local = sp_local + iVar3;
      if (c == 0) {
        return 0;
      }
      pc_local = pc_local + 1;
      break;
    case '\x06':
      iVar3 = chartorune(&c,sp_local);
      sp_local = sp_local + iVar3;
      if (c == 0) {
        return 0;
      }
      iVar3 = isnewline((uint)c);
      if (iVar3 != 0) {
        return 0;
      }
      pc_local = pc_local + 1;
      break;
    case '\a':
      iVar3 = chartorune(&c,sp_local);
      sp_local = sp_local + iVar3;
      if (c == 0) {
        return 0;
      }
      if ((flags & 1U) != 0) {
        iVar3 = canon(c);
        c = (Rune)iVar3;
      }
      if (c != pc_local->c) {
        return 0;
      }
      pc_local = pc_local + 1;
      break;
    case '\b':
      iVar3 = chartorune(&c,sp_local);
      sp_local = sp_local + iVar3;
      if (c == 0) {
        return 0;
      }
      if ((flags & 1U) == 0) {
        iVar3 = incclass(pc_local->cc,c);
        if (iVar3 == 0) {
          return 0;
        }
      }
      else {
        pRVar1 = pc_local->cc;
        iVar3 = canon(c);
        iVar3 = incclasscanon(pRVar1,(Rune)iVar3);
        if (iVar3 == 0) {
          return 0;
        }
      }
      pc_local = pc_local + 1;
      break;
    case '\t':
      iVar3 = chartorune(&c,sp_local);
      sp_local = sp_local + iVar3;
      if (c == 0) {
        return 0;
      }
      if ((flags & 1U) == 0) {
        iVar3 = incclass(pc_local->cc,c);
        if (iVar3 != 0) {
          return 0;
        }
      }
      else {
        pRVar1 = pc_local->cc;
        iVar3 = canon(c);
        iVar3 = incclasscanon(pRVar1,(Rune)iVar3);
        if (iVar3 != 0) {
          return 0;
        }
      }
      pc_local = pc_local + 1;
      break;
    case '\n':
      i = (int)out->sub[pc_local->n].ep - (int)out->sub[pc_local->n].sp;
      if ((flags & 1U) == 0) {
        iVar3 = strncmp(sp_local,out->sub[pc_local->n].sp,(long)i);
        if (iVar3 != 0) {
          return 0;
        }
      }
      else {
        iVar3 = strncmpcanon(sp_local,out->sub[pc_local->n].sp,i);
        if (iVar3 != 0) {
          return 0;
        }
      }
      if (0 < i) {
        sp_local = sp_local + i;
      }
      pc_local = pc_local + 1;
      break;
    case '\v':
      if ((sp_local == bol) && ((flags & 4U) == 0)) {
        pc_local = pc_local + 1;
      }
      else {
        if (((flags & 2U) == 0) ||
           ((sp_local <= bol || (iVar3 = isnewline((int)sp_local[-1]), iVar3 == 0)))) {
          return 0;
        }
        pc_local = pc_local + 1;
      }
      break;
    case '\f':
      if (*sp_local == '\0') {
        pc_local = pc_local + 1;
      }
      else {
        if (((flags & 2U) == 0) || (iVar3 = isnewline((int)*sp_local), iVar3 == 0)) {
          return 0;
        }
        pc_local = pc_local + 1;
      }
      break;
    case '\r':
      local_101 = false;
      if (bol < sp_local) {
        iVar3 = iswordchar((int)sp_local[-1]);
        local_101 = iVar3 != 0;
      }
      i = (int)local_101;
      uVar2 = iswordchar((int)*sp_local);
      i = uVar2 ^ i;
      if (i == 0) {
        return 0;
      }
      pc_local = pc_local + 1;
      break;
    case '\x0e':
      local_102 = false;
      if (bol < sp_local) {
        iVar3 = iswordchar((int)sp_local[-1]);
        local_102 = iVar3 != 0;
      }
      i = (int)local_102;
      iVar3 = iswordchar((int)*sp_local);
      if (iVar3 != i) {
        return 0;
      }
      pc_local = pc_local + 1;
      i = 0;
      break;
    case '\x0f':
      out->sub[pc_local->n].sp = sp_local;
      pc_local = pc_local + 1;
      break;
    case '\x10':
      out->sub[pc_local->n].ep = sp_local;
      pc_local = pc_local + 1;
      break;
    default:
      return 0;
    }
  } while( true );
}