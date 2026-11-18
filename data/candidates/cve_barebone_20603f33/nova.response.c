int readContigStripsIntoBuffer(FILE *fd, char *buf) {
    char *p = buf;
    int i, j, k, l, m, n, o, px, py, q, r, s, t, u, v, w, x, y, z;

    px = getc(fd);
    py = getc(fd);
    n = 0;
    m = fgetc(fd);
    if (m == 0) {
        sprintf(error, "premature EOF");
        return 0;
    }
    while (1) {
        for (i = 0; i < px; i++) {
            k = fgetc(fd);
            n = n / m;
            if (i < px - 1 && k!= py) {
                sprintf(error, "bad block checksum (%d of %d) in file \"%s\"",
                        k, py, input_file_name);
                if (n < 1 || stop) {
                    return 0;
                }
            }
        }
        p = p + n;
        i++;
    }
    return 1;
}