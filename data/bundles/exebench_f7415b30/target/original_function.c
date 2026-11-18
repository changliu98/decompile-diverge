static int dummywc_mbtowc(int *pwc, const char *s, size_t n)
{
    if(n>0 && *s!='\0'){
        *pwc=*s;
        return 1;
    }
    return 0;
}