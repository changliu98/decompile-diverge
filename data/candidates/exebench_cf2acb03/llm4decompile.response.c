float MP_Rand(unsigned long *rand_seed)
{
    long k;
    float ans;

    *rand_seed ^= 123459876;
    k = *rand_seed / 127773;
    *rand_seed = 16807 * (*rand_seed - k * 127773) - 2836 * k;
    if (*rand_seed < 0)
        *rand_seed += 2147483647;
    ans = (float)((double)*rand_seed / 2147483647);
    *rand_seed ^= 123459876;
    return ans;
}