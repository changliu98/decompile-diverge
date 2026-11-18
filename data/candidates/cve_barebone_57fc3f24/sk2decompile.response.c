static void handle_PORT(conn_t *conn, char *args) {
  struct sockaddr_in addr;
  char ip[16];
  int a, b, c, d, p1;
  if (conn->data_fd > 0) {
    uev_io_stop(&conn->data_watcher);
    close(conn->data_fd);
    conn->data_fd = -1;
  }
  sscanf(args, "%d,%d,%d,%d,%d", &a, &b, &c, &d, &p1);
  sprintf(ip, "%d.%d.%d.%d", a, b, c, d);
  if (!inet_aton(ip, &addr.sin_addr)) {
    send_msg(conn->fd, "500 Illegal PORT command.\r\n");
    return;
  }
  strlcpy(conn->data_ip, ip, sizeof(conn->data_ip));
  conn->data_port = p1 * 256 + a;
  send_msg(conn->fd, "200 PORT command successful.\r\n");
}