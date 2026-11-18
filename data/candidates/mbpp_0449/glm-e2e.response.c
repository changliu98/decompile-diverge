const char* func0(int a, int b, int c, int d, int e, int f) {
    int cross = a * (d - f) + b * (f - e) + c * (e - d);
    if (cross == 0) {
        return "on";
    } else {
        return "out";
    }
}