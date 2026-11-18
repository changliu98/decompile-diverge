int ft_pn(char *input_string, int *error_code, int index)
{
    // Skip leading whitespace and control characters
    while (input_string[index] == ' ' || input_string[index] <= '\b')
        index++;
    // If end of string is reached, set error code for empty input
    if (input_string[index] == '\0')
        *error_code = -3;
    // If first non-whitespace character is '-', set error code for negative sign
    else if (input_string[index] == '-')
        *error_code = -2;
    // Return the index of the first non-whitespace character
    return index;
}