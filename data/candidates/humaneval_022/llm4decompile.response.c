int * func0(char *values, int *size)
{
    int count = 0;
    char *end;
    char *start = values;

    while (*start) {
        while (*start && !((*__ctype_b_loc ())[(int) ((*start))] & 0x800) && *start != '-')
            ++start;

        if (*start) {
            int val = strtol(start, &end, 10);

            if (end != start && (*end == ',' || *end == '\0'))
                func0::out[count++] = val;

            while (*end && *end != ',')
                ++end;

            start = end;
        }
    }

    *size = count;
    return func0::out;
}