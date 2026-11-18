int stringmatchlen_fuzz_test(void)
{
    int i, j, cycles = 10000000, total_matches = 0;
    char str[32], pat[32];

    while (cycles--) {
        int slen = rand() % 32;
        int plen = rand() % 32;

        for (i = 0; i < slen; i++)
            str[i] = rand() % 128;

        for (i = 0; i < plen; i++)
            pat[i] = rand() % 128;

        total_matches += stringmatchlen(pat, plen, str, slen, 0);
    }

    return total_matches;
}