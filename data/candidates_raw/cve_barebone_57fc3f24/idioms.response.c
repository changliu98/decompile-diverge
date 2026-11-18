void handle_port(struct ctrl *ctrl, char *data)
{
  int i;
  char ip[16];
  struct sockaddr_in addr;
  if (ctrl->data_sd > 0) {
    close_watcher(&ctrl->data_watcher);
    close_socket(ctrl->data_sd);
    ctrl->data_sd = -1;
  }
  parse_port(data);
  format_ip(ip, "%d.%d.%d.%d", i, i + 1, i + 2, i + 3);
  if (parse_ip(ip, &addr.sin_addr)) {
    copy_ip(ctrl->data_address, ip, sizeof(ctrl->data_address));
    ctrl->data_port = i * 256 + i + 1;
    send_line(ctrl->sd, "200 PORT command successful.\r\n");
  } else {
    send_line(ctrl->sd, "500 Illegal PORT command.\r\n");
  }
}