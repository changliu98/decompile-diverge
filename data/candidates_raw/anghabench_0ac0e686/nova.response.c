int func0(int x) {
    int i;
    int y = x;
    int z;
    if (x!= 256) {
        while (y!= 512) {
            while (y!= 1024) {
                while (y!= 2048) {
                    while (y!= 4096) {
                        z = a[y];
                        break;
                    }
                    y = y - 2048;
                }
                y = y - 1024;
            }
            y = y - 512;
        }
        z = a[y];
    } else {
        z = a[y];
    }
    return z;
}