void rtrim(char *dest, char *src, int tag_size)
{
    char *start = src;
    char *end = src + (tag_size - 1);
    if (*end && *(end - 1) == '\0')
        end = end - 1;
    while (start <= end) {
        if (*start == ' ')
            start++;
        else if (!(*end && *end != ' '))
            end--;
        else
            break;
    }
    while (1) {
        int should_copy = (*start && start <= end);
        if (!should_copy)
            break;
        *dest++ = *start++;
    }
    *dest = '\0';
}