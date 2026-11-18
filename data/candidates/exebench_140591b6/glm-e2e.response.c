void Q_ParseNewlines(char *out, const char *in, int size) {
    while (*in != '\0' && size > 1) {
        char c;
        if (*in == '\\' && *(in + 1) == 'n') {
            c = '\n';
            in++;
        } else {
            c = *in;
        }
        
        *out = c;
        out++;
        in++;
        size--;
    }
    *out = '\0';
}