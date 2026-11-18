int setsize(unsigned long capacity,
    unsigned long *cyls, unsigned long *heads, unsigned long *secs)
{
 unsigned long hcyl, nsect, nhead;
 int ret = 0;

 hcyl = 1024 / 2;
 nsect = 60;
 nhead = capacity / (hcyl * nsect);
 if (nhead == 0) {
  nhead = 1024 / 2;
 } else if (nhead > 1024 / 2) {
  nhead = 1024 / 2;
  nsect = capacity / (hcyl * nhead);
  if (nsect > 60) {
   nsect = 60;
   hcyl = capacity / (nhead * nsect);
  }
 }

 if (hcyl == 0)
  ret = -1;
 *cyls = hcyl;
 *secs = nsect;
 *heads = nhead;
 return ret;
}