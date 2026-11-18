int vpf_str_to_num(const char *fmtstr, int *resnum)
{
    const char *sptr;
    int res;

    sptr = fmtstr;
    res = 0;
    while (*sptr && *sptr >= '0' && *sptr <= '9') {
        res = res * 10 + *sptr - '0';
        sptr++;
    }
    *resnum = res;
    return sptr - fmtstr;
}