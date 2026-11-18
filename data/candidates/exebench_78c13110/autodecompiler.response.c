void MotionToFrameCoord(int row, int col, int m, int n, int *newM, int *newN) {
    *newM = m + (row << 3);
    *newN = n + (col << 3);
}