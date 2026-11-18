void cgi_network_get_action(char *buffer) {
  int *buffer_int = (int *)buffer;
  buffer_int[1] = 2;
  buffer_int[2] = 1;
}