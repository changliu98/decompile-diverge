void __cdecl short_to_string(char *res, unsigned __int16 s)
{
    // Extract each digit by dividing and taking the remainder
    unsigned int ten_thousands = s / 10000;
    unsigned int thousands = (s / 1000) % 10;
    unsigned int hundreds = (s / 100) % 10;
    unsigned int tens = (s / 10) % 10;
    unsigned int ones = s % 10;

    // Convert digits to ASCII characters and write to the buffer
    res[0] = ten_thousands + '0';
    res[1] = thousands + '0';
    res[2] = hundreds + '0';
    res[3] = tens + '0';
    res[4] = ones + '0';
    
    // Null-terminate the string
    res[5] = '\0';
}