int stage1(rxvm_t *compiled, char *input, ir_stack_t **ret) {
 int err;
 context_t ctx;
 int state;

 if ((err = stage1_init(&ctx, ret)) < 0) {
  return err;
 }

 compiled->lfix0 = compiled->lfixn = 0;
 ctx.orig = input;
 state = 0;
 lex_init();
 while ((ctx.tok = lex(&input)) == 10) {
  ctx.simple = input;
  ctx.tok = 10;
 }

 if (ctx.tok == 15) {
  check_simple_for_lfix(compiled, ctx.orig);
  ctx.simple = ctx.orig;
  stage1_cleanup(&ctx);
  stack_free(ctx.prog, inst_stack_cleanup);
  *ret = NULL;
  return 0;
 }

 if (ctx.simple) {
  if ((err = compile_simple_backlog(&ctx)) < 0) {
   return -14;
  }
  ctx.simple = NULL;
 }

 while (ctx.tok >= 0) {
  if (state == 0) {
   if ((err = stage1_main_state(&ctx, &state)) < 0) {
    stage1_err_cleanup(&ctx);
    return err;
   }
  } else if (state == 1) {
   if ((err = stage1_charc_state(&ctx, &state)) < 0) {
    stage1_err_cleanup(&ctx);
    return err;
   }
  }
  ctx.lasttok = ctx.tok;
  ctx.tok = lex(&input);
  if (ctx.tok == 15) {
   break;
  }
 }

 if (ctx.lasttok == 4 && ctx.buf->size > 0) {
  stack_cat(ctx.prog, ctx.buf);
  free(ctx.buf);
  stack_free_head(ctx.parens);
 }

 if (state == 1) {
  stage1_err_cleanup(&ctx);
  return -6;
 }

 if (ctx.parens->head != ctx.parens->tail) {
  stage1_err_cleanup(&ctx);
  return -5;
 }

 lfix_stop();
 stack_cat(ctx.prog, ctx.parens->tail->data);
 attach_dangling_alt(&ctx);

 if ((err = code_match(&ctx)) < 0) {
  return err;
 }

 if (alt_seen) {
  compiled->lfix0 = 0;
  compiled->lfixn = 0;
 } else {
  compiled->lfix0 = get_lfix0();
  compiled->lfixn = get_lfixn();
 }

 ctx.prog->dsize = ctx.chained;
 stage1_cleanup(&ctx);
 return 0;
}