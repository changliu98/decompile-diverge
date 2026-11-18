int
ui_select(int in)
{
  if (g_tcp_sck == 0)
  {
    g_tcp_sck = in;
  }
  return 1;
}