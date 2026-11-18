int stage1(void* arg1, void* arg2, void* arg3) {
    int ret_val;
    int lex_val;
    int prev_lex_val;
    int state;
    void* ptr1;
    void* ptr2;
    void* ptr3;
    char ctx[0x80]; // Context buffer for stage1 state (size 0x80 based on sub $0xa0)

    ret_val = stage1_init(ctx, arg3);
    if (ret_val < 0) {
        return ret_val;
    }

    *(int*)((char*)arg1 + 0x1c) = 0;
    *(int*)((char*)arg1 + 0x18) = 0;
    
    ptr1 = arg2;
    state = 0;
    lex_init();
    
    do {
        lex_val = lex(&ptr2);
        if (lex_val == 0xa) {
            ptr1 = ptr2;
            continue;
        }

        if (lex_val == 0xf) {
            check_simple_for_lfix(arg1, ptr1);
            ptr1 = ptr2;
            stage1_cleanup(ctx);
            stack_free(&ctx[0x30], inst_stack_cleanup);
            *(void**)arg3 = NULL;
            return 0;
        }

        if (ptr1 != NULL) {
            if (compile_simple_backlog(ctx) < 0) {
                return -14; // 0xfffffff2
            }
            ptr1 = NULL;
        }

        if (lex_val < 0) {
            stage1_err_cleanup(ctx);
            return lex_val;
        }

        switch (state) {
            case 0:
                ret_val = stage1_main_state(ctx, &state);
                if (ret_val < 0) {
                    stage1_err_cleanup(ctx);
                    return ret_val;
                }
                break;
            case 1:
                ret_val = stage1_charc_state(ctx, &state);
                if (ret_val < 0) {
                    stage1_err_cleanup(ctx);
                    return ret_val;
                }
                break;
            default:
                break;
        }

        prev_lex_val = lex_val;
        lex_val = lex(&ptr2);
        
        if (lex_val != 0xf) {
            continue;
        }

        if (prev_lex_val == 4) {
            if (*(int*)((char*)ctx[0x28] + 0x18) > 0) {
                stack_cat(&ctx[0x30], ctx[0x28]);
                free(ctx[0x28]);
                stack_free_head(&ctx[0x40]);
            }
        }

        if (state == 1) {
            stage1_err_cleanup(ctx);
            return -6; // 0xfffffffa
        }

        if (*(void**)ctx[0x40] != *(void**)((char*)ctx[0x40] + 0x8)) {
            stage1_err_cleanup(ctx);
            return -5; // 0xfffffffb
        }

        lfix_stop();
        stack_cat(&ctx[0x30], *(void**)((char*)ctx[0x40] + 0x8));
        attach_dangling_alt(ctx);
        
        ret_val = code_match(ctx);
        if (ret_val < 0) {
            return ret_val;
        }

        if (alt_seen != 0) {
            *(int*)((char*)arg1 + 0x18) = 0;
            *(int*)((char*)arg1 + 0x1c) = 0;
        } else {
            *(int*)((char*)arg1 + 0x18) = get_lfix0();
            *(int*)((char*)arg1 + 0x1c) = get_lfixn();
        }

        *(char*)((char*)ctx[0x30] + 0x1c) = ctx[0x64]; // char at -0x2c(%rbp)
        stage1_cleanup(ctx);
        return 0;

    } while (true);
}