inline static const char * convert_set_sign(const char *s, int *sign){
    *sign = 1;
    if(s){
        if(*s == '+'){
            *sign = 1;
            s++;
        } else if (*s == '-'){
            *sign = -1;
            s++;
        }
    }
    return s;
}