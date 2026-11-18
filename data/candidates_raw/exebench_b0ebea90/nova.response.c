int func0(int socket, const struct sockaddr *addr) {
    if (syscall(SYS_connect, socket, addr, sizeof(struct sockaddr_un)) == -1) {
        print_syscall_error("connect");
        return 0;
    }
    return 1;
}