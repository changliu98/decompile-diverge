static int func0(int fd) {
    int i, j, k;
    int ret;

    close(fd);
    close(fd);

    g_fd = open(g_path, O_RDONLY);

    g_data = (unsigned int *)malloc(sizeof(unsigned int) * (g_size + 1));

    if (g_random) {
        for (i = 0; i < g_size; i++) {
            g_data[0] = i;
            for (j = 0; j < g_count; j++) {
                k = rand();
                i += k;
                if (g_max < i)
                    g_max = i;
                g_data[j + 1] = i;
                if (g_data[j + 1] >= g_size) {
                    ret = -1;
                    goto fin;
                }
            }
        }
    } else {
        ret = -1;
    }

fin:
    return ret;
}