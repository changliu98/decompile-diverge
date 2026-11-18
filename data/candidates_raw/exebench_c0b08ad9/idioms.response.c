void str_escape(char *out, char *in)
{
    int i = 0;
    int j = 0;
    for (i = 0, j = 0; out[i] != '\0'; i++, j++) {
        int c = in[j];
        if (c == '\0')
            break;
        if (c == '\t') {
            out[i++] = '\\';
            out[i++] = 't';
        }
        else if (c == '\n') {
            out[i++] = '\\';
            out[i++] = 'n';
        }
        else
            out[i] = c;
    }
}