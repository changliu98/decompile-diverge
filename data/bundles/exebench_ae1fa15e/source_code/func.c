
unsigned int render_uint32(unsigned int n, char* buff) {
 if(n == 0) { buff[0] = '0'; return 1; } unsigned int len = 0; for(; n > 0; n >>= 4) { buff[len++] = "0123456789ABCDEF"[n & 0xF]; } return len;
}
