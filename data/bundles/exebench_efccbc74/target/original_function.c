int
meat_time_which_month(
    unsigned char const * const
        p_arg,
    size_t const
        i_arg_len)
{
    static char const a_ref_month[12u][3u] =
    {
        { 'j', 'a', 'n' },
        { 'f', 'e', 'b' },
        { 'm', 'a', 'r' },
        { 'a', 'p', 'r' },
        { 'm', 'a', 'y' },
        { 'j', 'u', 'n' },
        { 'j', 'u', 'l' },
        { 'a', 'u', 'g' },
        { 's', 'e', 'p' },
        { 'o', 'c', 't' },
        { 'n', 'o', 'v' },
        { 'd', 'e', 'c' }
    };

    int
        i_month;

    char
        b_found;

    i_month =
        0;

    b_found =
        0;

    if (
        3u
        == i_arg_len)
    {
        while (
            !b_found && (i_month < 12))
        {
            if (
                (
                    p_arg[0u] == a_ref_month[i_month][0u])
                && (
                    p_arg[1u] == a_ref_month[i_month][1u])
                && (
                    p_arg[2u] == a_ref_month[i_month][2u]))
            {
                b_found = 1;
            }
            else
            {
                i_month ++;
            }
        }
    }

    if (
        !b_found)
    {
        i_month =
            -1;
    }

    return
        i_month;

}