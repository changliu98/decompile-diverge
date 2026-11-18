int *get_pentagonal(int n)
{
    int *arr = (int *)malloc(n * sizeof(int));
    int i, p, s;
    s = 0;
    p = 1;
    for(i = 1;; i++) {
        if(i > n) break;
        s += i;
        p *= i;
        if(i % 2 == 0) arr[i - 1] = p;
        else arr[i - 1] = s;
    }
    return arr;
}