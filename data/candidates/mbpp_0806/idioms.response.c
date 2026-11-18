int func0(char *str)
{
    int count = 0;
    int max = 0;
    int len = strlen(str);
    int i = 0;
    for (i = 0; i < len; i++) {
        if (((*__ctype_b_loc ())[(int) ((str[i]))] & (unsigned short) _ISupper)) {
            count++;
        } else {
            if (count > max) {
                max = count;
            }
            count = 0;
        }
    }
    if ((str[len - 1] != 0 && ((*__ctype_b_loc ())[(int) ((str[len - 1]))] & (unsigned short) _ISupper)) && (count > max)) {
        return count;
    }
    return max;
}