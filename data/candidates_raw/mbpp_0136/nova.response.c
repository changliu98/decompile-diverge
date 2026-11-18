double func0(int x) {
    double y;
    int a;
    if (x < 51) {
        y = 1.0 * x * 0.53;
        a = 25;
    } else if (x < 101) {
        y = 1.0 * (x - 50) * 0.58 + 5.5;
        a = 35;
    } else if (x < 201) {
        y = 1.0 * (x - 100) * 0.75 + 3.0 * 5.5;
        a = 45;
    } else {
        y = 1.0 * (x - 200) * 1.1 + 4.5 * 5.5;
        a = 75;
    }
    return y;
}