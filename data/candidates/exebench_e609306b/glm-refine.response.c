void __cdecl inet_get_local_port_range(int *low, int *high)
{
  if (low)
    *low = 1;
  if (high)
    *high = 1024;
}