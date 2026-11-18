int __cdecl stage1(rxvm_t *compiled, char *input, ir_stack_t **ret)
{
  context_t ctx; // [rsp+10h] [rbp-90h] BYREF
  int err; // [rsp+78h] [rbp-28h]
  int state; // [rsp+7Ch] [rbp-24h] BYREF
  ir_stack_t **reta; // [rsp+80h] [rbp-20h]
  char *inputa; // [rsp+88h] [rbp-18h] BYREF
  rxvm_t *compileda; // [rsp+90h] [rbp-10h]

  compileda = compiled;
  inputa = input;
  reta = ret;
  err = stage1_init(&ctx, ret);
  if ( err < 0 )
    return err;
  compileda->lfixn = 0;
  compileda->lfix0 = 0;
  ctx.orig = inputa;
  state = 0;
  lex_init();
  while ( 1 )
  {
    ctx.tok = lex(&inputa);
    if ( ctx.tok != 10 )
      break;
    ctx.simple = inputa;
  }
  if ( ctx.tok == 15 )
  {
    check_simple_for_lfix(compileda, ctx.orig);
    ctx.simple = ctx.orig;
    stage1_cleanup(&ctx);
    stack_free(ctx.prog, (void (*)(void *))inst_stack_cleanup);
    *reta = 0LL;
    return 0;
  }
  else
  {
    if ( !ctx.simple )
      goto LABEL_12;
    if ( compile_simple_backlog(&ctx) >= 0 )
    {
      ctx.simple = 0LL;
      do
      {
LABEL_12:
        if ( ctx.tok < 0 )
        {
          stage1_err_cleanup(&ctx);
          return ctx.tok;
        }
        if ( state )
        {
          if ( state == 1 )
          {
            err = stage1_charc_state(&ctx, &state);
            if ( err < 0 )
            {
LABEL_18:
              stage1_err_cleanup(&ctx);
              return err;
            }
          }
        }
        else
        {
          err = stage1_main_state(&ctx, &state);
          if ( err < 0 )
            goto LABEL_18;
        }
        ctx.lasttok = ctx.tok;
        ctx.tok = lex(&inputa);
      }
      while ( ctx.tok != 15 );
      if ( ctx.lasttok == 4 && ctx.buf->size > 0 )
      {
        stack_cat(ctx.prog, ctx.buf);
        free(ctx.buf);
        stack_free_head(ctx.parens);
      }
      if ( state == 1 )
      {
        stage1_err_cleanup(&ctx);
        return -6;
      }
      else if ( ctx.parens->head == ctx.parens->tail )
      {
        lfix_stop();
        stack_cat(ctx.prog, (ir_stack_t *)ctx.parens->tail->data);
        attach_dangling_alt(&ctx);
        err = code_match(&ctx);
        if ( err >= 0 )
        {
          if ( alt_seen )
          {
            compileda->lfix0 = 0;
            compileda->lfixn = 0;
          }
          else
          {
            compileda->lfix0 = get_lfix0();
            compileda->lfixn = get_lfixn();
          }
          ctx.prog->dsize = ctx.chained;
          stage1_cleanup(&ctx);
          return 0;
        }
        else
        {
          return err;
        }
      }
      else
      {
        stage1_err_cleanup(&ctx);
        return -5;
      }
    }
    else
    {
      return -14;
    }
  }
}