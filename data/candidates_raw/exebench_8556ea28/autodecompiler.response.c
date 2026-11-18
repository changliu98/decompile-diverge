void add_to_errbuf(int n, char **errbuf)
{
 if (!errbuf)
  return;
 *errbuf += n;
}