int tt_unesc(char *str, char ch) {
    int count;
    char *dest = str, *temp = str;

    while(1) {
        if(*temp == ch || *temp == '\0') {
            break;
        }
        temp++;
    }

    if(*temp == '\0') {
        return 0;
    }

    dest = temp;
    count = 0;

    while(1) {
        if(*temp == '\0') {
            break;
        }
        if(*temp == ch) {
            temp++;
            count++;
        }
        *dest = *temp;
        dest++;
        temp++;
    }
    return count;
}