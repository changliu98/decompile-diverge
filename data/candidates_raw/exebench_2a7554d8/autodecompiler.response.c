int strcremplace(char *str, char oldch, char newch)
{
    char *p;

    p = strchr(str, oldch);

    while(1) {
 if(p == NULL) break;
 *p = newch;
 p++;
 p = strchr(p, oldch);
    }

    return(0);
}