int foo(int *arr) {
    int val = 0;
    int i = 0;
    
    while (i < 10) {
        val = val + 1;
        arr[i] = val;
        i = i + 1;
    }
    
    return i + val;
}