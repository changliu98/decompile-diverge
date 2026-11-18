char *get_next_file(FILE *fp, char *buf)
{
    char *s = fgets(buf, 1024, fp);
    if(!s) {
        buf[0] = 0;
    }
    else {
        if(s[strlen(buf)-1] == '\n')
            buf[strlen(buf)-1] = 0;
    }
    return buf;
}