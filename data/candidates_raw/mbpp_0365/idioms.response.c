int get_len(int n){
    int len = 0;
    while(n != 0){
        n = n / 10;
        len++;
    }
    return len;
}