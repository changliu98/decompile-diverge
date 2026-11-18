int ui_select(int fd) {
    if (g_tcp_sck == 0) {
        g_tcp_sck = fd;
    }
    return 1;
}