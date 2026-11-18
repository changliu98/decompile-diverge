void put_num(unsigned_short *output_buffer, uint number, uchar digit_count)
{
    // If length is greater than 4, extract the 10,000s digit and write to destination
    if (4 < digit_count) {
        // Extract digit at 10^4 place, add 0x10 (likely for display encoding), and set high bits 0x2100
        *output_buffer = (short)(((ulong)number / 10000) % 10) + 0x10U | 0x2100;
        output_buffer++;
    }
    // If length is greater than 3, extract the 1,000s digit and write to destination
    if (3 < digit_count) {
        // Extract digit at 10^3 place, add 0x10, and set high bits 0x2100
        *output_buffer = (short)(((ulong)number / 1000) % 10) + 0x10U | 0x2100;
        output_buffer++;
    }
    // If length is greater than 2, extract the 100s digit and write to destination
    if (2 < digit_count) {
        // Extract digit at 10^2 place, add 0x10, and set high bits 0x2100
        *output_buffer = (short)(((ulong)number / 100) % 10) + 0x10U | 0x2100;
        output_buffer++;
    }
    // If length is greater than 1, extract the 10s digit and write to destination
    if (1 < digit_count) {
        // Extract digit at 10^1 place, add 0x10, and set high bits 0x2100
        *output_buffer = (short)(((ulong)number / 10) % 10) + 0x10U | 0x2100;
        output_buffer++;
    }
    // If length is non-zero, extract the 1s digit and write to destination
    if (digit_count != '\0') {
        // Extract digit at 10^0 place, add 0x10, and set high bits 0x2100
        *output_buffer = (short)(number % 10) + 0x10U | 0x2100;
    }
}