uLong __cdecl adler32_z(uLong adler, const Bytef *buf, z_size_t len)
{
    const Bytef *p = buf;
    z_size_t remaining = len;
    unsigned int sum2 = (adler >> 16) & 0xFFFF;
    unsigned int sum1 = adler & 0xFFFF;

    // If buf is NULL, return the initial Adler-32 value
    if (!buf)
        return 1;

    // Handle single-byte case
    if (len == 1)
    {
        sum1 += *buf;
        if (sum1 >= 0xFFF1)
            sum1 -= 0xFFF1;
        sum2 += sum1;
        if (sum2 >= 0xFFF1)
            sum2 -= 0xFFF1;
        return (sum2 << 16) | sum1;
    }

    // Handle short lengths (< 16 bytes)
    if (len < 16)
    {
        while (remaining--)
        {
            sum1 += *p++;
            sum2 += sum1;
        }
        if (sum1 >= 0xFFF1)
            sum1 -= 0xFFF1;
        return ((sum2 % 0xFFF1) << 16) | sum1;
    }

    // Process blocks of 5552 bytes (the maximum size before modulo is strictly required)
    while (remaining >= 5552)
    {
        remaining -= 5552;
        unsigned int n = 347; // 347 * 16 = 5552
        do
        {
            // Unrolled 16-byte loop
            sum1 += p[0];  sum2 += sum1;
            sum1 += p[1];  sum2 += sum1;
            sum1 += p[2];  sum2 += sum1;
            sum1 += p[3];  sum2 += sum1;
            sum1 += p[4];  sum2 += sum1;
            sum1 += p[5];  sum2 += sum1;
            sum1 += p[6];  sum2 += sum1;
            sum1 += p[7];  sum2 += sum1;
            sum1 += p[8];  sum2 += sum1;
            sum1 += p[9];  sum2 += sum1;
            sum1 += p[10]; sum2 += sum1;
            sum1 += p[11]; sum2 += sum1;
            sum1 += p[12]; sum2 += sum1;
            sum1 += p[13]; sum2 += sum1;
            sum1 += p[14]; sum2 += sum1;
            sum1 += p[15]; sum2 += sum1;
            p += 16;
            --n;
        } while (n);
        
        sum1 %= 0xFFF1;
        sum2 %= 0xFFF1;
    }

    // Process remaining bytes in 16-byte chunks
    if (remaining)
    {
        while (remaining >= 16)
        {
            remaining -= 16;
            sum1 += p[0];  sum2 += sum1;
            sum1 += p[1];  sum2 += sum1;
            sum1 += p[2];  sum2 += sum1;
            sum1 += p[3];  sum2 += sum1;
            sum1 += p[4];  sum2 += sum1;
            sum1 += p[5];  sum2 += sum1;
            sum1 += p[6];  sum2 += sum1;
            sum1 += p[7];  sum2 += sum1;
            sum1 += p[8];  sum2 += sum1;
            sum1 += p[9];  sum2 += sum1;
            sum1 += p[10]; sum2 += sum1;
            sum1 += p[11]; sum2 += sum1;
            sum1 += p[12]; sum2 += sum1;
            sum1 += p[13]; sum2 += sum1;
            sum1 += p[14]; sum2 += sum1;
            sum1 += p[15]; sum2 += sum1;
            p += 16;
        }
        
        // Process the final 1-15 bytes
        while (remaining--)
        {
            sum1 += *p++;
            sum2 += sum1;
        }
        
        sum1 %= 0xFFF1;
        sum2 %= 0xFFF1;
    }

    return (sum2 << 16) | sum1;
}