void
shift_line(int left, int round, int amount, int call_changed_bytes)
{
    int	    indent;
    int	    sw;

    sw = (int)get_sw_value_indent(curbuf);
    indent = get_indent();

    if (round)
    {
	if (indent % sw != 0 && left)
	    amount--;
	indent = left ? indent / sw - amount : indent / sw + amount;
	if (indent < 0)
	    indent = 0;
	indent *= sw;
    }
    else
    {
	indent = left ? indent - amount * sw : indent + amount * sw;
	if (indent < 0)
	    indent = 0;
    }

    if (State & 0x0200)
	change_indent(1L, (linenr_T)indent, (linenr_T)0, 0, call_changed_bytes);
    else
	set_indent(indent, call_changed_bytes != 0);
}