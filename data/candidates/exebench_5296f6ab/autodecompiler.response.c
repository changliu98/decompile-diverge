void charset_remove(char *string, unsigned char c) {
# 134 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/ipwndev/DSLinux-Mirror/refs/heads/master/user/replimenu/src/functions.h"
 char *dest = string;

 char *src = string;

 while (1) {
  if (*src == '\0') {
   *dest++ = '\0';
   return;
  } else if (*src != c) {
   *dest++ = *src;
  }
  src++;
 }
}