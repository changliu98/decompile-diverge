int __cdecl wfaCtrlRecv(int sock, unsigned __int8 *buf)
{
  return recv(sock, buf, 1023, 0);
}