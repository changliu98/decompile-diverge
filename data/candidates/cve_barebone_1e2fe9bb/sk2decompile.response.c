void beep_print(bee_ctx *ctx, const unsigned char *buf, unsigned len) {
  if (l_strnstart("MSG", 4, (const char *)buf, len))
    ctx->print(ctx, " BEEP MSG");
  else if (l_strnstart("RPY ", 4, (const char *)buf, len))
    ctx->print(ctx, " BEEP RPY");
  else if (l_strnstart("ERR ", 4, (const char *)buf, len))
    ctx->print(ctx, " BEEP ERR");
  else if (l_strnstart("ANS ", 4, (const char *)buf, len))
    ctx->print(ctx, " BEEP ANS");
  else if (l_strnstart("NUL ", 4, (const char *)buf, len))
    ctx->print(ctx, " BEEP NUL");
  else if (l_strnstart("SEQ ", 4, (const char *)buf, len))
    ctx->print(ctx, " BEEP SEQ");
  else if (l_strnstart("END", 4, (const char *)buf, len))
    ctx->print(ctx, " BEEP END");
  else
    ctx->print(ctx, " BEEP (payload or undecoded)");
}