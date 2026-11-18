int __cdecl wfaCtrlRecv(int sock, unsigned __int8 *buf)
{
  return recv(sock, buf, 0x3FFuLL, 0);
}