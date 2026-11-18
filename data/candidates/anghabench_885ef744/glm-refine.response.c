void __cdecl ui2a(unsigned int num, unsigned int base, int uc, char *bf)
{
    int n = 0;
    unsigned int numa = num;
    unsigned int d;

    // Find the highest divisor needed for the given number and base
    for (d = 1; num / d >= base; d *= base)
        ;

    while (d)
    {
        int dgt = numa / d;
        numa %= d;
        d /= base;

        // Skip leading zeros, but ensure we print at least one '0' if the number is 0
        if (n || dgt > 0 || !d)
        {
            char base_char;
            if (dgt >= 10)
            {
                // Use 'A' for uppercase hex, 'a' for lowercase hex
                base_char = uc ? 'A' : 'a';
            }
            else
            {
                base_char = '0';
            }
            *bf++ = base_char + (dgt % 10);
            ++n;
        }
    }
    *bf = '\0';
}