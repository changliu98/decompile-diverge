char* func0(int* arr, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        double val = (double)arr[i];
        double power = pow(10.0, (double)(n - 1 - i));
        sum += (int)(val * power);
    }
    
    char* result = (char*)malloc(12);
    sprintf(result, "%d", sum);
    
    return result;
}