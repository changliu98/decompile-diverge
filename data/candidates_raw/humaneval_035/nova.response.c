float func0(float arr[], int n) {
    float max = -30000;
    int i = 0;
    while (i < n) {
        if (arr[i] > max)
            max = arr[i];
        i++;
    }
    return max;
}