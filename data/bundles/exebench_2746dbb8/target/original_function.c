static void _uc(char *buf)
{
 for ( ; *buf; buf++) {
  if (*buf >= 'a' && *buf <= 'z') {
   *buf += 'A' - 'a';
  }
 }
}