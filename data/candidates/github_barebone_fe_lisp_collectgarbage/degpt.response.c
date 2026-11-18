void collectgarbage(fe_Context *ctx)

{
  char cVar1;
  fe_Object *pfVar2;
  fe_Object *obj;
  int i;
  fe_Context *ctx_local;
  
  for (i = 0; i < ctx->gcstack_idx; i = i + 1) {
    fe_mark(ctx,ctx->gcstack[i]);
  }
  fe_mark(ctx,ctx->symlist);
  for (i = 0; i < ctx->object_count; i = i + 1) {
    pfVar2 = ctx->objects + i;
    if (((pfVar2->car).c & 1U) == 0) {
      cVar1 = '\0';
    }
    else {
      cVar1 = (pfVar2->car).c >> 2;
    }
    if (cVar1 != '\x01') {
      if ((((pfVar2->car).c ^ 0xffU) & 2) == 0) {
        (pfVar2->car).c = (pfVar2->car).c & 0xfd;
      }
      else {
        if (((pfVar2->car).c & 1U) == 0) {
          cVar1 = '\0';
        }
        else {
          cVar1 = (pfVar2->car).c >> 2;
        }
        if ((cVar1 == '\n') && ((ctx->handlers).gc != (fe_CFunc)0x0)) {
          (*(ctx->handlers).gc)(ctx,pfVar2);
        }
        (pfVar2->car).c = '\x05';
        pfVar2->cdr = (Value)ctx->freelist;
        ctx->freelist = pfVar2;
      }
    }
  }
  return;
}