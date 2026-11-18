int stage1(rxvm_t *compiled,char *input,ir_stack_t **ret)

{
  int iVar1;
  uint uVar2;
  context_t ctx;
  int err;
  int state;
  ir_stack_t **ret_local;
  char *input_local;
  rxvm_t *compiled_local;
  int local_c;
  
  ret_local = ret;
  input_local = input;
  compiled_local = compiled;
  local_c = stage1_init(&ctx,ret);
  if (-1 < local_c) {
    compiled_local->lfixn = 0;
    compiled_local->lfix0 = 0;
    ctx.orig = input_local;
    state = 0;
    lex_init();
    while (ctx.tok = lex(&input_local), ctx.tok == 10) {
      ctx.simple = input_local;
      ctx.tok = 10;
    }
    if (ctx.tok == 0xf) {
      check_simple_for_lfix(compiled_local,ctx.orig);
      ctx.simple = ctx.orig;
      stage1_cleanup(&ctx);
      stack_free(ctx.prog,inst_stack_cleanup);
      *ret_local = (ir_stack_t *)0x0;
      local_c = 0;
    }
    else {
      if (ctx.simple != (char *)0x0) {
        iVar1 = compile_simple_backlog(&ctx);
        if (iVar1 < 0) {
          return -0xe;
        }
        ctx.simple = (char *)0x0;
      }
      do {
        if (ctx.tok < 0) {
          stage1_err_cleanup(&ctx);
          return ctx.tok;
        }
        if (state == 0) {
          iVar1 = stage1_main_state(&ctx,&state);
          if (iVar1 < 0) {
            stage1_err_cleanup(&ctx);
            return iVar1;
          }
        }
        else if ((state == 1) && (iVar1 = stage1_charc_state(&ctx,&state), iVar1 < 0)) {
          stage1_err_cleanup(&ctx);
          return iVar1;
        }
        ctx.lasttok = ctx.tok;
        ctx.tok = lex(&input_local);
      } while (ctx.tok != 0xf);
      if ((ctx.lasttok == 4) && (0 < (ctx.buf)->size)) {
        stack_cat(ctx.prog,ctx.buf);
        free(ctx.buf);
        stack_free_head(ctx.parens);
      }
      if (state == 1) {
        stage1_err_cleanup(&ctx);
        local_c = -6;
      }
      else if ((ctx.parens)->head == (ctx.parens)->tail) {
        lfix_stop();
        stack_cat(ctx.prog,(ctx.parens)->tail->data);
        attach_dangling_alt(&ctx);
        local_c = code_match(&ctx);
        if (-1 < local_c) {
          if (alt_seen == 0) {
            uVar2 = get_lfix0();
            compiled_local->lfix0 = uVar2;
            uVar2 = get_lfixn();
            compiled_local->lfixn = uVar2;
          }
          else {
            compiled_local->lfix0 = 0;
            compiled_local->lfixn = 0;
          }
          (ctx.prog)->dsize = (uint)ctx.chained;
          stage1_cleanup(&ctx);
          local_c = 0;
        }
      }
      else {
        stage1_err_cleanup(&ctx);
        local_c = -5;
      }
    }
  }
  return local_c;
}