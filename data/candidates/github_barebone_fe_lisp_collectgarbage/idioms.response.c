void collectgarbage(struct fe_Context *ctx)
{
  int i;
  for (i = 0; i < ctx->gcstack_idx; i++)
    fe_gc_mark(ctx, ctx->gcstack[i]);
  fe_gc_mark(ctx, ctx->symlist);
  for (i = 0; i < ctx->object_count; i++) {
    struct fe_Object *obj = &ctx->objects[i];
    int type;
    int mark;
    if (obj->car.c & 1)
      type = (obj->car.c >> 2);
    else
      type = 0;
    if (type == 1)
      continue;
    if (obj->car.c & 2) {
      if (obj->car.c & 1)
        mark = (obj->car.c >> 2);
      else
        mark = 0;
      if (mark == 10)
        if (ctx->handlers.gc)
          ctx->handlers.gc(ctx, obj);
      obj->car.c = 5;
      obj->cdr.o = ctx->freelist;
      ctx->freelist = obj;
    }
    else
      obj->car.c &= ~2;
  }
}