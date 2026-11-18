int func0(char c, float x, float y, float z, float *vx, float *vy, float *vz) {
    int i, j, k, n = 0;
    if (c < '0' || c > '9')
        return 0;
    i = c - '0';
    j = tbl[i + 1];
    k = tbl[i + 2] - 1;
    for (i = j; i <= k; i++) {
        int id = tbl_id[i];
        int id10 = id / 10;
        int id1 = id - id10 * 10;
        float dx = id10 * x;
        float dy = id1 * y;
        if (i!= k) {
            vx[n] = dx;
            vy[n] = dy;
            n++;
        }
        vx[n] = x - dx;
        vy[n] = y - dy;
        n++;
    }
    return n;
}