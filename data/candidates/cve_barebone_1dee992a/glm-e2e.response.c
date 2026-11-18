Reconstructed function
int eval_tuple(char **arg, void *rettv, void *evalarg, int flag) {
    bool is_vim9 = false;
    void *tuple = NULL;
    bool success = false;
    bool has_comma = false;
    void *tv; // typval_t tv; allocated on stack at -0x40(%rbp)
    bool is_legacy;

    if (evalarg == NULL) {
        is_legacy = false;
    } else {
        is_legacy = (*(int *)evalarg & 1) != 0;
    }

    is_vim9 = in_vim9script();

    if (!check_typval_is_value(rettv)) {
        clear_tv(rettv);
        return 0;
    }

    if (is_legacy) {
        tuple = tuple_alloc();
        if (tuple == NULL) {
            return 0;
        }
        if (*(int *)rettv != 0) {
            if (!tuple_append_tv(tuple, rettv)) {
                return 0;
            }
        }
    }

    if (**arg == ')') {
        goto done;
    }

    if (is_vim9) {
        char next_char = *(*arg + 1);
        if (next_char != ' ' && next_char != '\t' && next_char != '\n' && next_char != '\0' && next_char != ')') {
            semsg(e_white_space_required_after_str_str, *arg, e_missing_end_of_tuple_rsp_str + 24);
            goto fail;
        }
    }

    *arg = skipwhite_and_linebreak(*arg + 1, evalarg);

    while (**arg != ')' && **arg != '\0') {
        if (!eval1(arg, &tv, evalarg)) {
            goto fail;
        }

        if (!check_typval_is_value(&tv)) {
            if (is_legacy) {
                clear_tv(&tv);
            }
            goto fail;
        }

        if (is_legacy) {
            if (!tuple_append_tv(tuple, &tv)) {
                clear_tv(&tv);
                goto fail;
            }
        }

        if (!is_vim9) {
            *arg = skipwhite(*arg);
        }

        has_comma = (**arg == ',');

        if (has_comma) {
            if (is_vim9) {
                char next_char = *(*arg + 1);
                if (next_char != ' ' && next_char != '\t' && next_char != '\n' && next_char != '\0' && next_char != ')') {
                    semsg(e_white_space_required_after_str_str, *arg, e_missing_end_of_tuple_rsp_str + 24);
                    goto fail;
                }
            }
            *arg = skipwhite(*arg + 1);
        }

        *arg = skipwhite_and_linebreak(*arg, evalarg);

        if (**arg == ')') {
            break;
        }

        if (!has_comma) {
            if (flag != 0) {
                if (**arg == ',') {
                    semsg(e_no_white_space_allowed_before_str_str, *arg, e_missing_end_of_tuple_rsp_str + 24);
                } else {
                    semsg(e_missing_comma_in_tuple_str, *arg);
                }
            }
            goto fail;
        }
    }

    if (**arg != ')') {
        if (flag != 0) {
            semsg(e_missing_end_of_tuple_rsp_str, *arg);
        }
        goto fail;
    }

done:
    *arg = *arg + 1;

    if (is_legacy) {
        rettv_tuple_set(rettv, tuple);
    }

    return 1;

fail:
    if (is_legacy) {
        tuple_free(tuple);
    }
    return 0;
}