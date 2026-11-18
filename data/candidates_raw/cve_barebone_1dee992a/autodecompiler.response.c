static int
eval_tuple(char_u **pp, typval_T *rettv, evalarg_T *arg, int do_error)
{
    typval_T	*tp = NULL;
    typval_T	tv;
    int		tuple_eval = arg == NULL ? 0 : (arg->eval_flags & 0x01);
    int		vim9script = in_vim9script();
    int		has_comma;

    if (!check_typval_is_value(rettv))
    {
	clear_tv(rettv);
	return 0;
    }

    if (tuple_eval)
    {
	tp = tuple_alloc();
	if (tp == NULL)
	    return 0;
    }

    if (*(*pp) == ')' && !tuple_eval)
    {
	/* Empty tuple */
	goto done;
    }

    /* Skip white space and opening bracket. */
    if (tuple_eval || vim9script)
    {
	*pp = skipwhite_and_linebreak(*pp + 1, arg);
    }
    else
	*pp = skipwhite(*pp + 1);

    /* Loop over all items. */
    for (;;)
    {
	/* Allow white space before the item. */
	if (*(*pp) != ')' && *(*pp) != '\0')
	{
	    if (tuple_eval || vim9script)
	    {
		if (!((*pp)[1] == ' ' || (*pp)[1] == '\t'
			|| (*pp)[1] == '\n' || (*pp)[1] == '\0'
			|| (*pp)[1] == ')'))
		{
		    semsg("E1069: White space required after '%s': %s",
			    ",", *pp);
		    goto fail;
		}
	    }
	    else
		*pp = skipwhite(*pp);
	}

	/* Check for end of tuple. */
	if (**pp == ')')
	    break;

	/* Evaluate the item. */
	if (!eval1(pp, &tv, arg))
	    goto fail;
	if (!check_typval_is_value(&tv))
	{
	    if (tuple_eval)
		clear_tv(&tv);
	    goto fail;
	}

	if (tuple_eval)
	{
	    if (!tuple_append_tv(tp, &tv))
	    {
		clear_tv(&tv);
		goto fail;
	    }
	}
	else
	{
	    if (!vim9script)
		*pp = skipwhite(*pp);

	    /* Comma is optional here. */
	    has_comma = (**pp == ',');
	    if (has_comma)
	    {
		if (vim9script)
		{
		    if (!((*pp)[1] == ' ' || (*pp)[1] == '\t'
			    || (*pp)[1] == '\n' || (*pp)[1] == '\0'
			    || (*pp)[1] == ')'))
		    {
			semsg("E1069: White space required after '%s': %s",
				",", *pp);
			goto fail;
		    }
		}
		*pp = skipwhite(*pp + 1);
	    }

	    /* Skip white space after the item. */
	    *pp = skipwhite_and_linebreak(*pp, arg);

	    /* Check for end of tuple. */
	    if (**pp == ')')
		break;

	    /* Missing comma. */
	    if (!has_comma)
	    {
		if (do_error)
		{
		    if (**pp == ',')
			semsg("E1068: No white space allowed before '%s': %s",
				",", *pp);
		    else
			semsg("E1527: Missing comma in Tuple: %s", *pp);
		}
		goto fail;
	    }
	}
    }

    if (**pp != ')')
    {
	if (do_error)
	    semsg("E1526: Missing end of Tuple ')': %s", *pp);
	goto fail;
    }

done:
    ++*pp;
    if (tuple_eval)
	rettv_tuple_set(rettv, tp);
    return 1;

fail:
    if (tuple_eval)
	tuple_free(tp);
    return 0;
}