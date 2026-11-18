define LCG_INCREMENT  13849

void __cdecl rnd_between(long *prandom, long min, long max)
{
    long range = max + 1 - min;
    *prandom = min + (LCG_MULTIPLIER * (*prandom) + LCG_INCREMENT) % range;
}