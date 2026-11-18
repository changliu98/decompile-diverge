void sum(int n, char **errbuf)
{
 if (!errbuf)
  return;
 *errbuf += n;
}