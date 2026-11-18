static long next_comma(char *json, long len, long start, char end)
{
    int c;
    if (start == len)
        return - (start + 1);
    if (json[start] == ',')
        return start;
    for (;;) {
        c = json[start];
        if (c >= ' ' && c != '\r' && c != ' ')
            break;
        start++;
        if (start >= len)
            return - (start + 1);
    }
    if (json[start] == ',')
        return start;
    if (json[start] == end)
        return start;
    return - (start + 1);
}