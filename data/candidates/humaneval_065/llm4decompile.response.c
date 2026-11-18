char * func0(int x, int shift)
{
    sprintf(func0::xs, "%d", x);
    int len = strlen(func0::xs);
    if (shift >= len) {
        char temp[50];
        strcpy(temp, func0::xs + len - shift);
        temp[shift] = '\0';
        strncat(temp, func0::xs, len - shift);
        strcpy(func0::xs, temp);
    } else {
        for (int i = 0; i < len / 2; ++i) {
            char temp = func0::xs[i];
            func0::xs[i] = func0::xs[len - 1 - i];
            func0::xs[len - 1 - i] = temp;
        }
    }
    return func0::xs;
}