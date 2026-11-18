int* primes(int up, int *len) {
    int *p = (int*)malloc(sizeof(int)*up);
    *len = 0;
    int i, j, k, flag;
    for(i = 2; ; i++) {
        if(i >= up)
            break;
        flag = 1;
        for(j = 0; j < *len; j++) {
            k = p[j];
            if(k*k > i)
                break;
            if(i % k == 0) {
                flag = 0;
                break;
            }
        }
        if(flag) {
            p[*len] = i;
            (*len)++;
        }
    }
    return p;
}