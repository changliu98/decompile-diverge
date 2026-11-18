int __cdecl ui_select(int in)
{
  if ( !g_tcp_sck )
    g_tcp_sck = in;
  return 1;
}