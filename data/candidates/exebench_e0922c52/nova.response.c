void outfname(char *str) {
    if (*str!= '\0') {
        str++;
    } else {
        *(str - 1) ='s';
    }
}