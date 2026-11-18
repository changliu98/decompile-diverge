int
_chartorune(Rune *rune, const char *str)
{
 unsigned char c, c1, c2;

 c = *(unsigned char *)str;
 if(c < 0x80) {
  *rune = c;
  return 1;
 }

 c1 = *(unsigned char *)(str+1) ^ 0x80;
 if(c1 & 0xC0)
  goto invalid;
 if(c < 0xE0) {
  if(c < 0xC0 || c >= 0xC0+0x20)
   goto invalid;
  *rune = ((c & 0x1F)<<6) | c1;
  return 2;
 }

 c2 = *(unsigned char *)(str+2) ^ 0x80;
 if(c2 & 0xC0)
  goto invalid;
 if(c < 0xF0) {
  if(c < 0xE0 || c >= 0xE0+0x10)
   goto invalid;
  *rune = (((c & 0xF)<<6) | c1)<<6 | c2;
  return 3;
 }
# 104 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/r-lyeh/scriptorium/refs/heads/master/javascript/v7/v7.c"
invalid:
 *rune = 0x80;
 return 1;
}