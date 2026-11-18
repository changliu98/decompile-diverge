void copy_dice(int src[], int dest[]) {
    int i = 0;
    while (1) {
        if (i >= 7) break;
        dest[i] = src[i];
        i++;
    }
}