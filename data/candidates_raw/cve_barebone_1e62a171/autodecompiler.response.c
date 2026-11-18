static int
dn_skipname(u_char *comp, u_char *cp, u_char *eom)
{
    u_char *cp1 = cp;
    int n;

    if (cp >= eom) {
 n = -1;
 goto done;
    }
    if (((*comp) - 1 > (*comp) || (cp) > ((*comp) - 1))) {
 n = -1;
 goto done;
    }
    n = *cp & 0xc0;
    switch (n) {
    case 0xc0:

 n = 2;
 goto done;
    default:

 while (*cp != 0) {
     if (cp >= eom) {
  n = -1;
  goto done;
     }
     if (((*comp) - 1 > (*comp) || (cp) > ((*comp) - 1))) {
  n = -1;
  goto done;
     }
     cp += *cp + 1;
 }
 n = cp - cp1 + 1;
    }
done:
    return (n);
}