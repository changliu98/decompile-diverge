void str_copy(char *s, char *t)
{
    for(;;s++, t++) {
        if(*t == '\0') {
            *s = '\0';
            return;
        }
        *s = *t;
    }
}