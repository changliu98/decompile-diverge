int __cdecl unix_socketpair(int d, int type, int protocol, int *sv)
{
  return socketpair(d, type, protocol, sv);
}