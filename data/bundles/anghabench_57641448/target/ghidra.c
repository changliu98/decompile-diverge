int ui_select(int in)

{
  int in_local;
  
  if (g_tcp_sck == 0) {
    g_tcp_sck = in;
  }
  return 1;
}