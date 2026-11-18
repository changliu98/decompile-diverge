void find_ibm(int a, int b, int *out1, int *out2) {
    int v1 = (a - 0xa1) * 0x9d + b - 0x3f;
    if (b > 0x7e) {
        v1--;
    }
    
    int v2 = (v1 != 0) ? 0x22 : 0;
    if (v2 > 0x198) {
        v2 += 0x5d;
    }
    
    int v3 = v2 % 0xbc + 0x89;
    int v4 = v2 - (v2 % 0xbc) * 0xbc + 0x3f;
    
    if (v4 > 0x7e) {
        v4++;
    }
    
    *out1 = v3;
    *out2 = v4;
}