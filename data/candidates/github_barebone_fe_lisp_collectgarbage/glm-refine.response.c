void __cdecl collectgarbage(fe_Context *ctx)
{
  fe_Object *obj;
  int type;
  int i;

  // 1. Mark phase: Mark all reachable objects
  for (i = 0; i < ctx->gcstack_idx; ++i)
    fe_mark(ctx, ctx->gcstack[i]);
  fe_mark(ctx, ctx->symlist);

  // 2. Sweep phase: Free unmarked objects
  for (i = 0; i < ctx->object_count; ++i)
  {
    obj = &ctx->objects[i];

    // Determine the object's type ID
    if ((obj->car.c & 1) != 0)
      type = obj->car.c >> 2;
    else
      type = 0;

    // If the object is NOT a primitive type 1 (which is never freed)
    if (type != 1)
    {
      // Check if the object is NOT marked (reachable)
      if ((obj->car.c & 2) == 0)
      {
        // If it's a type 10 object, invoke its garbage collection handler
        if (type == 10 && ctx->handlers.gc)
          ctx->handlers.gc(ctx, obj);

        // Add the object to the free list
        obj->car.c = 5; // 5 = (1 | 4), marking it as a freed pointer of type 1
        obj->cdr.o = ctx->freelist;
        ctx->freelist = obj;
      }
      else
      {
        // Object is marked: clear the mark bit for the next GC cycle
        obj->car.c &= ~2u;
      }
    }
  }
}