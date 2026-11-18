char* func0(char* s)
{
    int i, length, nletter;
    char temp;

    nletter = 0;
    length = strlen(s);
    for (i = 0; i < length; i++) {
        if (!((*__ctype_b_loc ())[(int) ((unsigned char) s[i])] & 0x400))
            nletter++;
        else if ((*__ctype_b_loc ())[(int) ((unsigned char) s[i])] & 0x100)
            s[i] = tolower((unsigned char) s[i]);
        else if ((*__ctype_b_loc ())[(int) ((unsigned char) s[i])] & 0x200)
            s[i] = toupper((unsigned char) s[i]);
    }

    if (nletter == length) {
        for (i = 0; i < length / 2; i++) {
            temp = s[i];
            s[i] = s[length - i - 1];
            s[length - i - 1] = temp;
        }
    }

    return s;
}