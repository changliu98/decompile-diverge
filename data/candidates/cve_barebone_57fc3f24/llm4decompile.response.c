void handle_PORT(ctrl_t *ctrl, char *str)
{
    int a, b, c, d, e, f;
    char addr[16];
    struct sockaddr_in sin;

    if (ctrl->data_sd > 0) {
        uev_io_stop(&ctrl->data_watcher);
        close(ctrl->data_sd);
        ctrl->data_sd = -1;
    }

    __isoc99_sscanf(str, "%d,%d,%d,%d,%d,%d", &a, &b, &c, &d, &e, &f);
    sprintf(addr, "%d.%d.%d.%d", a, b, c, d);
    if (!inet_aton(addr, &sin.sin_addr)) {
        send_msg(ctrl->sd, "500 Illegal PORT command.\r\n");
        return;
    }

    strlcpy(ctrl->data_address, addr, 16);
    ctrl->data_port = e * 256 + f;
    send_msg(ctrl->sd, "200 PORT command successful.\r\n");
}