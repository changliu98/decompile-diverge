static void collectgarbage(fe_Context *ctx) {
  int i;
  /* mark */
  for (i = 0; i < ctx->gcstack_idx; i++) {
    fe_mark(ctx, ctx->gcstack[i]);
  }
  fe_mark(ctx, ctx->symlist);
  /* sweep and unmark */
  for (i = 0; i < ctx->object_count; i++) {
    fe_Object *obj = &ctx->objects[i];
    if (type(obj) == FE_TFREE) { continue; }
    if (~tag(obj) & GCMARKBIT) {
      if (type(obj) == FE_TPTR && ctx->handlers.gc) {
        ctx->handlers.gc(ctx, obj);
      }
      settype(obj, FE_TFREE);
      cdr(obj) = ctx->freelist;
      ctx->freelist = obj;
    } else {
      tag(obj) &= ~GCMARKBIT;
    }
  }
}