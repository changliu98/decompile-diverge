float func0(float arr[], int n) {
    float sum = 0;
    int i = 0;
    for (i = 0; i < n; i++) {
        sum += arr[i];
    }
    float avg = sum / n;
    float sd = -1;
    for (i = 0; i < n; i++) {
        sd += pow(arr[i] - avg, 2);
    }
    return sd / n;
}