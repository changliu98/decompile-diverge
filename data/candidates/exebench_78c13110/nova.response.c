void MotionToFrameCoord(int i, int j, int m, int n, int *p, int *q) {
    *p = i * 8 + m;
    *q = j * 8 + n;
}