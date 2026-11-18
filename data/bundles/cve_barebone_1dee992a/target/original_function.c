int
eval_tuple(char_u **arg, typval_T *rettv, evalarg_T *evalarg, int do_error)
{
    int		evaluate = evalarg == NULL ? FALSE
					 : evalarg->eval_flags & EVAL_EVALUATE;
    tuple_T	*tuple = NULL;
    typval_T	tv;
    int		vim9script = in_vim9script();
    int		had_comma;

    if (check_typval_is_value(rettv) == FAIL)
    {
	// the first item is not a valid value type
	clear_tv(rettv);
	return FAIL;
    }

    if (evaluate)
    {
	tuple = tuple_alloc();
	if (tuple == NULL)
	    return FAIL;

	if (rettv->v_type != VAR_UNKNOWN)
	{
	    // Add the first item to the tuple from "rettv"
	    if (tuple_append_tv(tuple, rettv) == FAIL)
		return FAIL;
	}
    }

    if (**arg == ')')
	// empty tuple
	goto done;

    if (vim9script && !IS_WHITE_NL_OR_NUL((*arg)[1]) && (*arg)[1] != ')')
    {
	semsg(_(e_white_space_required_after_str_str), ",", *arg);
	goto failret;
    }

    *arg = skipwhite_and_linebreak(*arg + 1, evalarg);
    while (**arg != ')' && **arg != NUL)
    {
	if (eval1(arg, &tv, evalarg) == FAIL)	// recursive!
	    goto failret;
	if (check_typval_is_value(&tv) == FAIL)
	{
	    if (evaluate)
		clear_tv(&tv);
	    goto failret;
	}

	if (evaluate)
	{
	    if (tuple_append_tv(tuple, &tv) == FAIL)
	    {
		clear_tv(&tv);
		goto failret;
	    }
	}

	if (!vim9script)
	    *arg = skipwhite(*arg);

	// the comma must come after the value
	had_comma = **arg == ',';
	if (had_comma)
	{
	    if (vim9script && !IS_WHITE_NL_OR_NUL((*arg)[1]) && (*arg)[1] != ')')
	    {
		semsg(_(e_white_space_required_after_str_str), ",", *arg);
		goto failret;
	    }
	    *arg = skipwhite(*arg + 1);
	}

	// The ")" can be on the next line.  But a double quoted string may
	// follow, not a comment.
	*arg = skipwhite_and_linebreak(*arg, evalarg);
	if (**arg == ')')
	    break;

	if (!had_comma)
	{
	    if (do_error)
	    {
		if (**arg == ',')
		    semsg(_(e_no_white_space_allowed_before_str_str),
								    ",", *arg);
		else
		    semsg(_(e_missing_comma_in_tuple_str), *arg);
	    }
	    goto failret;
	}
    }

    if (**arg != ')')
    {
	if (do_error)
	    semsg(_(e_missing_end_of_tuple_rsp_str), *arg);
failret:
	if (evaluate)
	    tuple_free(tuple);
	return FAIL;
    }

done:
    *arg += 1;
    if (evaluate)
	rettv_tuple_set(rettv, tuple);

    return OK;
}