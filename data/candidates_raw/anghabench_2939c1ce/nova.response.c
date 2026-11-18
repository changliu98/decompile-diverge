void func0(void *obj) {
    unsigned char *p = (unsigned char *)obj;
    unsigned char tmp = p[0];
    p[0] = p[3];
    p[3] = tmp;
    tmp = p[1];
    p[1] = p[2];
    p[2] = tmp;
}