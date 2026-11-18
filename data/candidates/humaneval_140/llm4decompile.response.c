void func0(char *text, char *out)
{
    int i, j, space_len;

    space_len = 0;
    for (i = 0, j = 0; i < strlen(text); i++) {
        if (text[i] == ' ') {
            space_len++;
            continue;
        }

        if (space_len == 1) {
            out[j++] = '_';
        }
        if (space_len == 2) {
            out[j++] = '_';
            out[j++] = '_';
        }
        if (space_len > 2) {
            out[j++] = '-';
        }
        space_len = 0;

        out[j++] = text[i];
    }

    if (space_len == 1) {
        out[j++] = '_';
    }
    if (space_len == 2) {
        out[j++] = '_';
        out[j++] = '_';
    }
    if (space_len > 2) {
        out[j++] = '-';
    }
    out[j++] = '\0';
}