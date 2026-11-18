void func0(const char *message, char *out)
{
    int i, j;
    char c, vowels[10] = "aeiouAEIOU";

    for (i = 0; message[i] != 0; i++) {
        c = message[i];
        if (isupper(c))
            c = toupper(c);
        else if (islower(c))
            c = tolower(c);

        for (j = 0; vowels[j] != 0; j++) {
            if (c == vowels[j]) {
                if (j < 10)
                    c += 2;
                break;
            }
        }
        out[i] = c;
    }
    out[i] = 0;
}