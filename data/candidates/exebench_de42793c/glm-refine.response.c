int __cdecl conv_hstring(const char *string, unsigned int *num)
{
    int pos = 0;
    *num = 0;

    while (1)
    {
        char c = string[pos];
        bool is_valid = false;

        // Check if the character is a valid hexadecimal digit
        if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))
        {
            // Ensure the string length does not exceed 9 characters
            is_valid = (pos < 9);
        }

        if (!is_valid)
            break;

        // Convert the hex character to its integer value and accumulate
        if (c >= 'a' && c <= 'f')
            *num = (*num << 4) + (c - 'a' + 10);
        else
            *num = (*num << 4) + (c - '0');

        pos++;
    }

    return pos;
}