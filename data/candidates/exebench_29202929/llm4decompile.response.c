char *mystpcpy(char *to, char *from)
{
    while ((*to++ = *from++))
        ;
    return --to;
}