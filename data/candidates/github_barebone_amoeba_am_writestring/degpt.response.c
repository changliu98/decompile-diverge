int am_writestring(am_DumpCtx *ctx,char *name)

{
  am_Dumper *paVar1;
  int iVar2;
  size_t sVar3;
  ulong local_40;
  size_t buflen;
  size_t namelen;
  am_Dumper *d;
  char *name_local;
  am_DumpCtx *ctx_local;
  
  paVar1 = ctx->dumper;
  if (name == (char *)0x0) {
    local_40 = 0;
  }
  else {
    local_40 = strlen(name);
  }
  if ((0xff < local_40) || (0xff < local_40)) {
    return -1;
  }
  if (local_40 < 0x20) {
    iVar2 = am_writechar(ctx,(int)local_40 + 0xa0);
    if (iVar2 != 0) {
      return -1;
    }
  }
  else {
    iVar2 = am_writechar(ctx,0xd9);
    if (iVar2 != 0) {
      return -1;
    }
    iVar2 = am_writechar(ctx,(int)local_40);
    if (iVar2 != 0) {
      return -1;
    }
  }
  sVar3 = (long)ctx->p - (long)ctx->buf;
  if (0x1000 < sVar3 + local_40) {
    ctx->p = ctx->buf;
    if (sVar3 != 0) {
      iVar2 = (*paVar1->writer)(paVar1,ctx->buf,sVar3);
      ctx->ret = iVar2;
      if (iVar2 != 0) {
        return -1;
      }
    }
    if (0x1000 < local_40) {
      iVar2 = (*paVar1->writer)(paVar1,name,local_40);
      ctx->ret = iVar2;
      return iVar2;
    }
  }
  memcpy(ctx->p,name,local_40);
  ctx->p = ctx->p + local_40;
  return 0;
}