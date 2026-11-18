void removeCharactersInPlace (char *aString, const char *excludeChars)
{
    char *read = aString;
    char *write = aString;
    char *exclude;
    char c, x;

    while ((c = *read++)) {
        for (exclude = (char *) excludeChars; (x = *exclude++);) {
            if (c == x) break;
        }
        if (c != x) *write++ = c;
    }
    *write = '\0';
}