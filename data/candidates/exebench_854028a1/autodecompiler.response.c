void
closep(int *sock)
{
 if (*sock >= 0) {
  close(*sock);
 }
 *sock = -1;
}