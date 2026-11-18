int __cdecl stage1(rxvm_t *compiled, char *input, ir_stack_t **ret)
{
  context_t ctx;
  int err;
  int state = 0;

  err = stage1_init(&ctx, ret);
  if (err < 0)
    return err;

  compiled->lfixn = 0;
  compiled->lfix0 = 0;
  ctx.orig = input;
  
  lex_init();
  
  while (1)
  {
    ctx.tok = lex(&input);
    if (ctx.tok != 10)
      break;
    ctx.simple = input;
  }

  if (ctx.tok == 15)
  {
    check_simple_for_lfix(compiled, ctx.orig);
    ctx.simple = ctx.orig;
    stage1_cleanup(&ctx);
    stack_free(ctx.prog, (void (*)(void *))inst_stack_cleanup);
    *ret = 0LL;
    return 0;
  }

  if (ctx.simple && compile_simple_backlog(&ctx) < 0)
    return -14;

  ctx.simple = 0LL;
  
  while (1)
  {
    if (ctx.tok < 0)
    {
      stage1_err_cleanup(&ctx);
      return ctx.tok;
    }

    if (state == 1)
      err = stage1_charc_state(&ctx, &state);
    else
      err = stage1_main_state(&ctx, &state);

    if (err < 0)
    {
      stage1_err_cleanup(&ctx);
      return err;
    }

    ctx.lasttok = ctx.tok;
    ctx.tok = lex(&input);
    
    if (ctx.tok == 15)
      break;
  }

  if (ctx.lasttok == 4 && ctx.buf->size > 0)
  {
    stack_cat(ctx.prog, ctx.buf);
    free(ctx.buf);
    stack_free_head(ctx.parens);
  }

  if (state == 1)
  {
    stage1_err_cleanup(&ctx);
    return -6;
  }

  if (ctx.parens->head != ctx.parens->tail)
  {
    stage1_err_cleanup(&ctx);
    return -5;
  }

  lfix_stop();
  stack_cat(ctx.prog, (ir_stack_t *)ctx.parens->tail->data);
  attach_dangling_alt(&ctx);
  
  err = code_match(&ctx);
  if (err < 0)
    return err;

  if (alt_seen)
  {
    compiled->lfix0 = 0;
    compiled->lfixn = 0;
  }
  else
  {
    compiled->lfix0 = get_lfix0();
    compiled->lfixn = get_lfixn();
  }

  ctx.prog->dsize = ctx.chained;
  stage1_cleanup(&ctx);
  return 0;
}