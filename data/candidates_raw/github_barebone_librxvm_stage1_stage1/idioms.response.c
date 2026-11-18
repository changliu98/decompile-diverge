int compile_backlog(struct rxvm *vm, char *in, struct ir_stack **ret)
{
  int state;
  int err;
  struct context ctx;
  ctx.in = in;
  ctx.ret = ret;
  err = stage1_init(&ctx);
  if (err < 0)
    return err;
  vm->lfixn = 0;
  vm->lfix0 = 0;
  ctx.orig = ctx.in;
  state = 0;
  lex_init();
  while (ctx.tok == 10) {
    ctx.simple = ctx.in;
    ctx.in = lex(&ctx.in);
  }
  if (ctx.tok == 15) {
    check_simple_for_lfix(vm, ctx.orig);
    ctx.simple = ctx.orig;
    stage1_cleanup(&ctx);
    stack_free(ctx.prog, inst_stack_cleanup);
    *ctx.ret = ((void *)0);
    return 0;
  }
  if (ctx.simple) {
    if (compile_simple_backlog(&ctx) < 0)
      return -14;
    ctx.simple = ((void *)0);
  }
  do {
    if (ctx.tok < 0) {
      stage1_err_cleanup(&ctx);
      return ctx.tok;
    }
    if (state == 0) {
      err = stage1_main_state(&ctx, &state);
      if (err < 0) {
        stage1_err_cleanup(&ctx);
        return err;
      }
    } else if (state == 1) {
      err = stage1_charc_state(&ctx, &state);
      if (err < 0) {
        stage1_err_cleanup(&ctx);
        return err;
      }
    }
    ctx.lasttok = ctx.tok;
    ctx.in = lex(&ctx.in);
  } while (ctx.in != 15);
  if (ctx.lasttok == 4 && ctx.buf->size > 0) {
    stack_cat(ctx.prog, ctx.buf);
    free(ctx.buf);
    stack_free_head(ctx.parens);
  }
  if (state == 1) {
    stage1_err_cleanup(&ctx);
    return -6;
  }
  if (ctx.parens->head == ctx.parens->tail) {
    lfix_stop();
    stack_cat(ctx.prog, ctx.parens->tail->data);
    attach_dangling_alt(&ctx);
    err = code_match(&ctx);
    if (err < 0)
      return err;
    if (alt_seen) {
      vm->lfixn = vm->lfix0 = 0;
    } else {
      vm->lfix0 = get_lfix0();
      vm->lfixn = get_lfixn();
    }
    ctx.prog->dsize = ctx.chained;
    stage1_cleanup(&ctx);
    return 0;
  }
  stage1_err_cleanup(&ctx);
  return -5;
}