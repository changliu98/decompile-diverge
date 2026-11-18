char* func0(int coefX, int coefY, int sum) {
    static char func0_result[50];
    char* result;
    int x, y;

    for (x = 0; ; x++) {
        if (coefX * x > sum)
            break;

        if ((sum - coefX * x) % coefY == 0) {
            y = (sum - coefX * x) / coefY;
            sprintf(func0_result, "x = %d, y = %d", x, y);
            result = func0_result;
            break;
        }
    }

    if (x == 0 || x > sum)
        result = "No solution";

    return result;
}