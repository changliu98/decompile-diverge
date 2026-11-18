int func0(char c) {
    int is_alnum;

    if (c <= 32)
        is_alnum = 0;
    else {
        int ascii = c;

        if (ascii == '*' || ascii == ':' || ascii == '<' || ascii == '>' ||
            ascii == '?' || ascii == '|' || ascii == '\\' || ascii == '\'')
            is_alnum = 0;
        else
            is_alnum = 1;
    }
    return (is_alnum);
}