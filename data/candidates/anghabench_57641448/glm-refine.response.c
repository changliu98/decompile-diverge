int ui_select(int socket_fd)
{
  if (!g_tcp_sck) {
    g_tcp_sck = socket_fd;
  }
  
  return 1;
}