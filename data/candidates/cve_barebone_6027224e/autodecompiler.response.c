static int
shift_line(int dir, int round, int amount, int call_changed_bytes)
{
    int		sw = get_sw_value_indent(curbuf);
    int		ind;
    int		n;
    int		rem;

    ind = get_indent();

    if (round)
    {
	/* Round to sw */
	n = ind / sw;
	rem = ind % sw;
	if (rem && dir)
	    --amount;
	if (dir)
	{
	    n -= amount;
	    if (n < 0)
		n = 0;
	}
	else
	    n += amount;
	ind = n * sw;
    }
    else
    {
	if (dir)
	{
	    ind -= sw * amount;
	    if (ind < 0)
		ind = 0;
	}
	else
	    ind += sw * amount;
    }

    if (State & 0x0200)
	return change_indent(1, ind, NULL, 0, call_changed_bytes);
    return set_indent(ind, call_changed_bytes ? TRUE : FALSE);
}