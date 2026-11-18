void __cdecl collectgarbage(fe_Context *ctx)
{
  int v1; // [rsp+0h] [rbp-20h]
  int v2; // [rsp+4h] [rbp-1Ch]
  fe_Object *obj; // [rsp+8h] [rbp-18h]
  int i; // [rsp+14h] [rbp-Ch]
  int ia; // [rsp+14h] [rbp-Ch]

  for ( i = 0; i < ctx->gcstack_idx; ++i )
    fe_mark(ctx, ctx->gcstack[i]);
  fe_mark(ctx, ctx->symlist);
  for ( ia = 0; ia < ctx->object_count; ++ia )
  {
    obj = &ctx->objects[ia];
    if ( (obj->car.c & 1) != 0 )
      v2 = obj->car.c >> 2;
    else
      v2 = 0;
    if ( v2 != 1 )
    {
      if ( (~obj->car.c & 2) != 0 )
      {
        if ( (obj->car.c & 1) != 0 )
          v1 = obj->car.c >> 2;
        else
          v1 = 0;
        if ( v1 == 10 )
        {
          if ( ctx->handlers.gc )
            ctx->handlers.gc(ctx, obj);
        }
        obj->car.c = 5;
        obj->cdr.o = ctx->freelist;
        ctx->freelist = obj;
      }
      else
      {
        obj->car.c &= ~2u;
      }
    }
  }
}