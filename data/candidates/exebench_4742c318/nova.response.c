float mayorDif(float arr[]) {
    float max, min, diff;
    max = min = diff = 0.0;
    for (int i = 0;; i++) {
        if (arr[i + 1] == 0) {
            break;
        }
        diff = arr[i] - arr[i + 1];
        if (diff >= 0) {
            max = diff;
        } else {
            max = -diff;
        }
        diff = max;
        if (diff > min) {
            min = diff;
        }
    }
    return min;
}