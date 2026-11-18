void collectgarbage(fe_Context *ctx) {
  int i;


  for (i = 0; i < ctx->gcstack_idx; i++)
    fe_mark(ctx, ctx->gcstack[i]);


  fe_mark(ctx, ctx->symlist);


  for (i = 0; i < ctx->object_count; i++) {
    fe_Object *obj = &ctx->objects[i];


    if ((((intptr_t)(obj->car.c) & 1) ? ((intptr_t)(obj->car.c) >> 2) : 0) == 1)
      continue;


    if ((((intptr_t)(obj->car.c) & 1) ? 0 : ((intptr_t)(obj->car.c) & 2)) == 0) {
      ((obj->car.c) = ((intptr_t)(obj->car.c) & ~2));
      continue;
    }


    if ((((intptr_t)(obj->car.c) & 1) ? ((intptr_t)(obj->car.c) >> 2) : 0) == 10) {
      if (ctx->handlers.gc)
        ctx->handlers.gc(ctx, obj);
    }


    ((obj->car.c) = ((intptr_t)(5) << 2));
    obj->cdr.o = ctx->freelist;
    ctx->freelist = obj;
  }
}