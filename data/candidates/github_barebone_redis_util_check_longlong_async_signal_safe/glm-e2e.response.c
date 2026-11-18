char* check_longlong_async_signal_safe(char *s, int *err) {
    *err = 0;
    
    if (*s == 'l') {
        s++;
        if (*s != 'l') {
            *err = 1;
        } else {
            s++;
            *err = 1;
        }
    }
    
    return s;
}