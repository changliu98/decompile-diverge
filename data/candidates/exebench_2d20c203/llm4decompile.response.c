char *str_rev(char *s)
{
    char *t,*h;
    for(t=s;*t;t++);
    for(h=s;h<--t;h++){
        *h^=*t;
        *t^=*h;
        *h^=*t;
    }
    return s;
}