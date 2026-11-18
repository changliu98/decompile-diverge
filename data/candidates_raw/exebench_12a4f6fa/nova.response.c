static void func0(char *p, unsigned short val) {
    char *h = p;
    *p = '\0';
    for (p -= 1; p >= h; p--) {
        *p = (val & 0x7) + '0';
        val >>= 3;
        if (p!= h) {
            unsigned char c = (val & 0x7) + '0';
            if (val)
                val >>= 3;
            else
                c ='';
            *--p = c;
        }
    }
}