int stage1 (rxvm_t *compiled, char *input, ir_stack_t **ret)
{
    int state;
    int err;
    context_t ctx;

    if ((err = stage1_init(&ctx, ret)) < 0)
        return err;

    compiled->lfix0 = compiled->lfixn = 0;
    ctx.orig = input;
    state = STATE_START;
    lex_init();

    while ((ctx.tok = lex(&input)) == LITERAL) {
        ctx.simple = input;
    }

    /* String contains only literal characters;
     * no compilation necessary. */
    if (ctx.tok == END) {
#ifndef NOEXTRAS
        check_simple_for_lfix(compiled, ctx.orig);
#endif /* NOEXTRAS */
        ctx.simple = ctx.orig;
        stage1_cleanup(&ctx);
        stack_free(ctx.prog, inst_stack_cleanup);
        *ret = NULL;
        return 0;
    } else if (ctx.simple) {
        if (compile_simple_backlog(&ctx) < 0) {
            return RXVM_EMEM;
        }

        ctx.simple = NULL;
    }

    do {
        if (ctx.tok < 0) {
            stage1_err_cleanup(&ctx);
            return ctx.tok;
        }

        switch (state) {
            case STATE_START:
                /* if it's not a character class, then all the
                 * metacharacters apply-- run the main state. */
                if ((err = stage1_main_state(&ctx, &state)) < 0) {
                    stage1_err_cleanup(&ctx);
                    return err;
                }

            break;
            case STATE_CHARC:
                /* inside character class-- run character class state */
                if ((err = stage1_charc_state(&ctx, &state)) < 0) {
                    stage1_err_cleanup(&ctx);
                    return err;
                }

            break;
        }

        ctx.lasttok = ctx.tok;
    } while ((ctx.tok = lex(&input)) != END);

    if (ctx.lasttok == RPAREN && ctx.buf->size > 0) {
        stack_cat(ctx.prog, ctx.buf);
        free(ctx.buf);
        stack_free_head(ctx.parens);
    }

    if (state == STATE_CHARC) {
        stage1_err_cleanup(&ctx);
        return RXVM_ECLASS;
    } else if (ctx.parens->head != ctx.parens->tail) {
        stage1_err_cleanup(&ctx);
        return RXVM_EPAREN;
    }

    /* End of input-- anything left in the buffer
     * can be appended to the output. */
#ifndef NOEXTRAS
    lfix_stop();
#endif /* NOEXTRAS */
    stack_cat(ctx.prog, (ir_stack_t *) ctx.parens->tail->data);
    attach_dangling_alt(&ctx);

    /* Add the match instruction */
    if ((err = code_match(&ctx)) < 0) {
        return err;
    }

#ifndef NOEXTRAS
    if (alt_seen) {
        compiled->lfix0 = 0;
        compiled->lfixn = 0;
    } else {
        compiled->lfix0 = get_lfix0();
        compiled->lfixn = get_lfixn();
    }
#endif /* NOEXTRAS */

    /* Re-use dsize member to indicate to stage2 whether
     * jmp chain optimisation is needed */
    ctx.prog->dsize = ctx.chained;
    stage1_cleanup(&ctx);
    return 0;
}