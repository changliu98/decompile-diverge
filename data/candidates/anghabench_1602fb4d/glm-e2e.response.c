int mode1112(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9) {
    int v1 = a1;
    int v2 = a2;
    int v3 = a3;
    int v4 = a4;
    int v5 = a5;
    int v6 = a6;
    
    int sum = (v1 << 2) + ((v3 + v5 + v6 + a7) << 1) + v2 + v4 + a8 + a9;
    
    return (sum + 8) >> 4;
}