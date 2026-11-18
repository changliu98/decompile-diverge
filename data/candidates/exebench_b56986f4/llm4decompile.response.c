void makeipt(int nw, int ip[])
{
 int j, l;

 ip[1] = 0;
 ip[2] = 0;
 ip[3] = 16;
 l = 2;
 while (nw > 32) {
  for (j = l; j < l * 2; ++j) {
   ip[j + l] = ip[j] * 4;
   ip[j + l * 2] = ip[j] * 4 + l * 16;
  }
  nw = nw / 4;
  l = l * 2;
 }
}