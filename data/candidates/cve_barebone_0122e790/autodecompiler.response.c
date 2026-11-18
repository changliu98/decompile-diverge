static char *parse_content_length(char *s, char *e, int *n)
{
    char *p;
    int i, c;

    p = s;
    while (1) {
 if ((p < e && (*p == ' ' || *p == '\t' || (*p == '\r' && *(p + 1) == '\n') || (*p == '\n' && (*(p + 1) == ' ' || *(p + 1) == '\t')))) {
 } else {
     break;
 }
 p++;
    }
    if (p == e) return error();
    i = 0;
    c = 0;
    while (1) {
 if ((p < e && *p >= '0' && *p <= '9')) {
     c = c * 10 + *p - '0';
     if (c < 0) return NULL;
     i++;
     p++;
 } else {
     break;
 }
    }
    if (p == e || i == 0) return error();
    while (1) {
 if ((p < e && (*p == ' ' || *p == '\t' || (*p == '\n' && (*(p + 1) == ' ' || *(p + 1) == '\t'))))) {
 } else {
     break;
 }
 p++;
    }
    if (p == e) return error();
    if (*p++ != '\n' && (*p++ != '\r' || *p++ != '\n')) return error();
    *n = c;
    return p;
}