static void clean_fd(int sock, int *cache_sock, int *nsock) {
    int i;
    for (i = 0; i < 2; i++) {
        if (cache_sock[i] == sock)
            cache_sock[i] = 0;
    }

    close(sock);
    (*nsock)--;
}