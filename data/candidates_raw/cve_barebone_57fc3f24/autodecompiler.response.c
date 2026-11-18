static void cmd_port(ftp_session_t *session, char *arg)
{
 int i[6];
 char ip[16];

 if (session->data_sock > 0) {
  uev_io_stop(&session->data_watcher);
  close(session->data_sock);
  session->data_sock = -1;
 }

 ___isoc99_sscanf(arg, "%d,%d,%d,%d,%d,%d", &i[0], &i[1], &i[2],
   &i[3], &i[4], &i[5]);
 sprintf(ip, "%d.%d.%d.%d", i[0], i[1], i[2], i[3]);

 if (!inet_aton(ip, &session->client_addr.sin_addr)) {
  while (0)
   ;
  goto err;
 }

 strlcpy(session->client_ip, ip, sizeof(session->client_ip));
 session->client_addr.sin_port = (i[4] << 8) + i[5];

 return;

err:
 send_msg(session->control_fd, "500 Illegal PORT command.\r\n");
}