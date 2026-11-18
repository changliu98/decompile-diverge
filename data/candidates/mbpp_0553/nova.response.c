float func0(int x, int y) {
    int i = 0, j = y;
    if (j == 0)
        i = 1;
    while (j!= 0) {
        if (j!= 0) {
            i++;
            j = j / 10;
        }
    }
    return (float)(x + pow(10, i - 1)) / (float)pow(10, i);
}