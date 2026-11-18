int
meat_time_which_month(
    const char *p_arg,
    size_t i_arg_len)
{
    int i_month;
    char b_found;

    i_month = 0;
    b_found = 0;

    if (i_arg_len == 3)
    {
        while ((! b_found) && (i_month < 12))
        {
            if (
                (p_arg[0] == a_ref_month[i_month][0])
             && (p_arg[1] == a_ref_month[i_month][1])
             && (p_arg[2] == a_ref_month[i_month][2]))
            {
                b_found = 1;
            }
            else
            {
                i_month++;
            }
        }
    }

    if (b_found)
    {
        return i_month;
    }
    else
    {
        return -1;
    }
}