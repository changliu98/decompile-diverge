char * func0(char * text)
{
    int i, j;
    for (i = 0, j = 0; text[i] != 0; i++) {
        if ((*__ctype_b_loc ())[(int) ((text[i]))] & 0x100) {
            if (i > 0 && ((*__ctype_b_loc ())[(int) ((text[i - 1]))] & 0x200 || (*__ctype_b_loc ())[(int) ((text[i - 1]))] & 0x800)) {
                func0::buffer[j++] = '_';
            }
            func0::buffer[j++] = tolower(text[i]);
        } else {
            func0::buffer[j++] = text[i];
        }
    }
    func0::buffer[j] = 0;
    return func0::buffer;
}