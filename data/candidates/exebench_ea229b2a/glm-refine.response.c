const char *__cdecl convert_set_sign(const char *str, int *sign)
{
    // Default sign is positive (1)
    *sign = 1;

    // Check for null pointer to prevent access violations
    if (str != NULL)
    {
        // Check for '+' (ASCII 43)
        if (*str == '+')
        {
            *sign = 1;
            return str + 1;
        }
        // Check for '-' (ASCII 45)
        else if (*str == '-')
        {
            *sign = -1;
            return str + 1;
        }
    }

    // Return the original pointer if null or no sign prefix is found
    return str;
}