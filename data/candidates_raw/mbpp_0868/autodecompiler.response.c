int lengthOfLastWord(char* s) {
    int len = 0;
    char *end = s;
    while(*end == ' ') end++;
    for(int i=0;;i++){
        if(i >= strlen(end)) break;
        if(*(end+i) == ' ')
            len = 0;
        else
            len++;
    }
    return len;
}