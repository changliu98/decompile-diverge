float func0(float x, float t[], int n) {
    int i, j, k;
    float y;
    if (x == t[0])
        y = -1;
    else if (x < t[0])
        y = -2;
    else if (x == t[n - 1])
        y = n - 1;
    else if (x > t[n - 1])
        y = n;
    else {
        for (i = 0; i <= n - 1; i++) {
            j = (i + n) / 2;
            if (x < t[j])
                n = j - 1;
            else if (x > t[j])
                i = j + 1;
            else {
                y = (x - t[n]) / (t[i] - t[n]);
                y = (1 - y) * t[n] + y * t[i];
                break;
            }
        }
    }
    return y;
}