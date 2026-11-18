char *
strcpyend(char *to, char *from)

{
    while ((*to++ = *from++) != '\0');
    return(--to);
}