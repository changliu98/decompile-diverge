void handle_PORT(struct Context *ctx, const char *arg) {
    int h1, h2, h3, h4, p1, p2;
    char ip_buf[32]; // -0x40 to -0x20
    struct in_addr addr; // -0x50 to -0x4c

    if (ctx->data_fd > 0) {
        uev_io_stop(&ctx->watcher);
        close(ctx->data_fd);
        ctx->data_fd = -1;
    }

    sscanf(arg, "%d,%d,%d,%d,%d,%d", &h1, &h2, &h3, &h4, &p1, &p2);

    sprintf(ip_buf, "%d.%d.%d.%d", h1, h2, h3, h4);

    if (inet_aton(ip_buf, &addr) != 0) {
        strlcpy(ctx->ip_str, ip_buf, 16);
        ctx->port = (p1 << 8) + p2;
        send_msg(ctx->sock_fd, "200 PORT command successful");
    } else {
        send_msg(ctx->sock_fd, "500 Illegal PORT command");
    }
}