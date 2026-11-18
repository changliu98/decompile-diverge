void __cdecl misc_str_remove_symbol(char *str, char symbol)
{
    int read_idx = 0;
    int write_idx = 0;

    // Iterate through the string until the null terminator is encountered
    while (str[read_idx] != '\0')
    {
        // If the current character is not the target symbol, keep it
        if (str[read_idx] != symbol)
        {
            str[write_idx++] = str[read_idx];
        }
        read_idx++;
    }

    // Null-terminate the modified string
    str[write_idx] = '\0';
}