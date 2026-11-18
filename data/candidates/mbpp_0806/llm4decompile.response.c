int func0(char *test_str)
{
    int len = strlen(test_str);
    int max = 0;
    int cnt = 0;
    int idx = 0;

    for (idx = 0; idx < len; idx++)
    {
        if (0 != (0x0100 & (__ctype_b_loc ( )->mask [ (int) (test_str [idx]) ])))
        {
            cnt++;
        }
        else
        {
            if (cnt > max)
            {
                max = cnt;
            }
            cnt = 0;
        }
    }

    if (0 != (0x0100 & (__ctype_b_loc ( )->mask [ (int) (test_str [len - 1]) ])))
    {
        if (cnt > max)
        {
            max = cnt;
        }
    }

    return max;
}