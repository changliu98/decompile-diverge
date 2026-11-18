int stage1(re_match_context_t *mctx, char *regexp, re_dfa_t **dfa) {
  stage1_context_t sctx;
  int err;
  int state;
  err = stage1_init(&sctx, dfa);
  if (err < 0) return err;
  mctx->lfix0 = 0;
  mctx->lfixn = 0;
  sctx.regexp = regexp;
  state = 0;
  lex_init();
  sctx.curr_tok = lex(&regexp);
  if (sctx.curr_tok == '\n') {
    sctx.backlog = regexp;
    sctx.curr_tok = lex(&regexp);
  }
  if (sctx.curr_tok == 15) {
    check_simple_for_lfix(mctx, sctx.regexp);
    sctx.backlog = sctx.regexp;
    stage1_cleanup(&sctx);
    stack_free(sctx.code, (void (*)(void *))code_free);
    *dfa = NULL;
    return 0;
  }
  if (sctx.backlog) {
    if (compile_simple_backlog(&sctx) < 0) return -14;
    sctx.backlog = NULL;
  }
  while (1) {
    if (sctx.curr_tok < 0) {
      stage1_err_cleanup(&sctx);
      return sctx.curr_tok;
    }
    if (state == 0) {
      err = stage1_main_state(&sctx, &state);
      if (err < 0) {
        stage1_err_cleanup(&sctx);
        return err;
      }
    } else if (state == 1) {
      err = stage1_charc_state(&sctx, &state);
      if (err < 0) {
        stage1_err_cleanup(&sctx);
        return err;
      }
    }
    sctx.prev_tok = sctx.curr_tok;
    sctx.curr_tok = lex(&regexp);
    if (sctx.curr_tok == 15) {
      if (sctx.prev_tok == 4 && sctx.alt->size > 0) {
        stack_cat(sctx.code, sctx.alt);
        free(sctx.alt);
        stack_free_head(sctx.alt_stack);
      }
      if (state == 1) {
        stage1_err_cleanup(&sctx);
        return -6;
      }
      if (sctx.alt_stack->size != sctx.alt_stack->head) {
        stage1_err_cleanup(&sctx);
        return -5;
      }
      lfix_stop();
      stack_cat(sctx.code, sctx.alt_stack->head->data);
      attach_dangling_alt(&sctx);
      err = code_match(&sctx);
      if (err < 0) return err;
      if (lfix_disabled) {
        mctx->lfix0 = 0;
        mctx->lfixn = 0;
      } else {
        mctx->lfix0 = get_lfix0();
        mctx->lfixn = get_lfixn();
      }
      sctx.code->match_func = sctx.match_func_ptr;
      stage1_cleanup(&sctx);
      return 0;
    }
  }
}