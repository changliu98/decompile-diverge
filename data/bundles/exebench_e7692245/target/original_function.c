void dwordstore(char *p, const int d)
{
 p[0] = d & 0xff;
 p[1] = (d >> 8) & 0xff;
 p[2] = (d >> 16) & 0xff;
 p[3] = (d >> 24) & 0xff;
 return;
}