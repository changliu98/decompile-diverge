char * base91(char *output_buffer, int value)
{
    // Encode the higher-order digit of base91 representation
    // i / 0x5b gives the quotient, add '!' (ASCII 33) to map to base91 character set
    *output_buffer = (char)(value / 0x5b) + '!';
    
    // Encode the lower-order digit of base91 representation
    // i % 0x5b gives the remainder, add '!' (ASCII 33) to map to base91 character set
    output_buffer[1] = (char)(value % 0x5b) + '!';
    
    // Return pointer advanced by 2 positions (since two characters were written)
    return output_buffer + 2;
}