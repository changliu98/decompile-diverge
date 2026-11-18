void set_stimulus(struct prime_ctx *__restrict ctx, const char *__restrict p) {
   for (; *p; p++) {
      if (*p >= '0' && *p <= '7')
         ctx->stimulus &= 0xff ^ (1 << (*p - '0'));
   }
}