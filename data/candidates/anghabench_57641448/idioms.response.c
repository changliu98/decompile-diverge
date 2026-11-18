int ui_select(int sck)
{
  if (g_tcp_sck == 0)
    g_tcp_sck = sck;
  return 1;
}