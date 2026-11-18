int
eval_tuple(char_u **expr, typval_T *tv, evalarg_T *evalarg, int do_error)
{
    int		is_list = evalarg != NULL && (evalarg->eval_flags & 1);
    tuple_T	*tuple = NULL;
    int		vim9script = in_vim9script();

    if (!check_typval_is_value(tv))
    {
	clear_tv(tv);
	return 0;
    }

    if (is_list)
    {
	tuple = tuple_alloc();
	if (tuple == NULL)
	    return 0;
	if (tv->v_type != VAR_UNKNOWN && !tuple_append_tv(tuple, tv))
	    return 0;
    }

    if (**expr == ')')
    {
	++*expr;
	if (is_list)
	    rettv_tuple_set(tv, tuple);
	return 1;
    }

    /* In Vim9 script a comma is always required after the first item. */
    if (vim9script && !(((*expr)[1]) == ' ' || (*expr)[1] == '\t' || (*expr)[1] == '\n' || (*expr)[1] == NUL || (*expr)[1] == ')'))
    {
	semsg("E1069: White space required after '%s': %s", ",", *expr);
	goto theend;
    }

    *expr = skipwhite_and_linebreak(*expr + 1, evalarg);

    for (;;)
    {
	typval_T	tv2;
	int		evaluate;
	int		had_comma;

	if (**expr == ')' || **expr == NUL)
	    break;

	evaluate = eval1(expr, &tv2, evalarg);
	if (evaluate == 0)
	    goto theend;

	if (!check_typval_is_value(&tv2))
	{
	    if (is_list)
		clear_tv(&tv2);
	    goto theend;
	}

	if (is_list && !tuple_append_tv(tuple, &tv2))
	{
	    clear_tv(&tv2);
	    goto theend;
	}

	if (!vim9script)
	    *expr = skipwhite(*expr);

	had_comma = **expr == ',';
	if (had_comma)
	{
	    /* In Vim9 script a comma must always be followed by a space. */
	    if (vim9script && !(((*expr)[1]) == ' ' || (*expr)[1] == '\t' || (*expr)[1] == '\n' || (*expr)[1] == NUL || (*expr)[1] == ')'))
	    {
		semsg("E1069: White space required after '%s': %s", ",", *expr);
		goto theend;
	    }
	    *expr = skipwhite(*expr + 1);
	}

	*expr = skipwhite_and_linebreak(*expr, evalarg);

	if (**expr == ')')
	    break;

	if (!had_comma)
	{
	    if (do_error)
	    {
		if (**expr == ',')
		    semsg("E1068: No white space allowed before '%s': %s",
			    ",", *expr);
		else
		    semsg("E1527: Missing comma in Tuple: %s", *expr);
	    }
	    goto theend;
	}
    }

    if (**expr == ')')
    {
	++*expr;
	if (is_list)
	    rettv_tuple_set(tv, tuple);
	return 1;
    }

    if (do_error)
	semsg("E1526: Missing end of Tuple ')': %s", *expr);

theend:
    if (is_list)
	tuple_free(tuple);

    return 0;
}