const unsigned char *smb_fdata(smb_ctx *ctx, const unsigned char *p,
                               const char *fmt, const unsigned char *end,
                               int flags) {
  const unsigned char *p1;
  char buf[128];
  char *p2;
  int len;
  while (*fmt) {
    switch (*fmt) {
      case '#':
        fmt++;
        return p;
      case '%':
        fmt++;
        p = end;
        break;
      case '*':
        fmt++;
        while (p < end) {
          smb_fdata_level++;
          p1 = smb_fdata(ctx, p, fmt, end, flags);
          smb_fdata_level--;
          if (p1 == NULL) return NULL;
          if (p1 == p) return p;
          p = p1;
        }
        return p;
      case '[':
        fmt++;
        if (p >= end) return p;
        memset(buf, 0, sizeof(buf));
        p2 = strchr(fmt, ']');
        len = p2 - fmt + 1;
        if (len > sizeof(buf)) return p;
        strncpy(buf, fmt, len - 1);
        buf[len - 1] = '\0';
        fmt = p2 + 1;
        p = smb_fdata1(ctx, p, buf, end, flags);
        if (p == NULL) return NULL;
        break;
      case '|':
        fmt++;
        if (p >= end) return p;
        break;
      default:
        ctx->print(ctx, "%c", *fmt);
        fmt++;
        break;
    }
  }
  if (smb_fdata_level == 0 && p < end) {
    len = end - p;
    ctx->print(ctx, "Data: (%lu bytes)\n", (unsigned long)len);
    smb_print_data(ctx, p, len);
    p += len;
  }
  return p;
}