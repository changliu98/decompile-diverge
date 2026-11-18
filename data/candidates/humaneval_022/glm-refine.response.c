Assuming this is defined globally elsewhere

int *__cdecl func0(const char *input_str, int *out_size)
{
    char *end;
    const char *start;
    int val;
    int count = 0;

    for (start = input_str; *start; start = end)
    {
        // Skip whitespace
        while (*start && (isspace(*start) || *start == '-'))
        {
            ++start;
        }

        if (!*start)
            break;

        val = strtol(start, &end, 10);

        // Check if strtol successfully parsed a number.
        // It fails if it didn't consume any characters, or if the next character
        // isn't a comma or the end of the string.
        if (start == end || (*end != ',' && *end != '\0'))
        {
            // Parsing failed: skip characters until we hit a comma or the end of the string
            while (*end && *end != ',')
            {
                ++end;
            }
        }
        else
        {
            // Parsing succeeded: store the value
            func0_out[count++] = val;
        }
    }

    *out_size = count;
    return func0_out;
}