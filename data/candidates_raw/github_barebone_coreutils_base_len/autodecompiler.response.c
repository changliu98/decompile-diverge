size_t
get_base_len(char *path)
{
 size_t len = strlen(path);
 size_t base_len;

 for (;;) {
  char c = (len > 1) ? path[len - 1] : '\0';
  if (c == '/') {
   len--;
   continue;
  }
  break;
 }

 base_len = 0;
# 347 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/sergecodd/FireFox-OS/refs/heads/master/B2G/gecko/ipc/chromium/src/third_party/libevent/test-internal.c"
 return len;
}