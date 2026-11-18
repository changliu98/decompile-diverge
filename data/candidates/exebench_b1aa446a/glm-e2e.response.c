char* get_mod_and_div(long *mod_out, long *div_out, char *sign_pos, long num) {
    if (num < 0) {
        *mod_out = -(num % 10);
        *div_out = -(num / 10);
        *sign_pos = '-';
        sign_pos++;
    } else {
        *mod_out = num % 10;
        *div_out = num / 10;
    }
    
    return sign_pos;
}