int func0(char **dict, int size)
{
    int i;
    int j;
    int has_lower;
    int has_upper;
    char *word;
    if (size == 0)
        return 0;
    has_lower = 0;
    has_upper = 0;
    for (i = 0; i < size; i++) {
        word = dict[i * 2];
        for (j = 0; word[j]; j++) {
            if (!((*__ctype_b_loc ())[(int) ((word[j]))] & (unsigned short) _ISalnum))
                return 0;
            if (((*__ctype_b_loc ())[(int) ((word[j]))] & (unsigned short) _ISupper))
                has_upper = 1;
            if (((*__ctype_b_loc ())[(int) ((word[j]))] & (unsigned short) _ISlower))
                has_lower = 1;
            if (has_upper + has_lower == 2)
                return 0;
        }
    }
    return 1;
}