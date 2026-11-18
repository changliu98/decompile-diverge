int func0(char **dict, int size)
{
    int i, j;
    int has_upper, has_lower;
    char *word;

    if (size == 0)
        return 0;

    has_upper = 0;
    has_lower = 0;
    for (i = 0; i < size; i++) {
        word = dict[i];
        for (j = 0; word[j] != '\0'; j++) {
            if (!((*__ctype_b_loc ())[(int) ((unsigned char) word[j])] & 0x0400))
                return 0;
            if ((*__ctype_b_loc ())[(int) ((unsigned char) word[j])] & 0x0100)
                has_upper = 1;
            if ((*__ctype_b_loc ())[(int) ((unsigned char) word[j])] & 0x0200)
                has_lower = 1;
            if (has_upper + has_lower == 2)
                return 0;
        }
    }

    return 1;
}