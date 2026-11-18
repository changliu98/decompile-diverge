void pick(int *np, int *nr)
{
    *nr += 1;
    if (*nr >= 768) {
        *np += 1;
        *nr = 0;
    }
    if (*np >= 180) {
        *np = 0;
    }
}