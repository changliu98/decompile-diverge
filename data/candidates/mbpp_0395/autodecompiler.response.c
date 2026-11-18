int func0(char* s) {
    int set[256];
    char order[256];
    memset(set,0,256*sizeof(int));
    int len = strlen(s);
    int i;
    int cnt = 0;
    for(i=0;i<len;++i){
        char c = s[i];
        if(!set[c]){
            order[cnt++] = c;
        }
        ++set[c];
    }
    for(i=0;i<cnt;++i){
        char c = order[i];
        if(set[c]==1){
            return c;
        }
    }
    return '\0';
}