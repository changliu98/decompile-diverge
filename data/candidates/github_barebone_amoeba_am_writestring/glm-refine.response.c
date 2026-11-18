int __cdecl am_writestring(am_DumpCtx *ctx, const char *name)
{
  int write_ret;
  size_t name_len;
  size_t buf_len;
  am_Dumper *dumper;

  dumper = ctx->dumper;
  
  // Calculate string length safely
  name_len = name ? strlen(name) : 0;

  // Enforce maximum string length of 255 bytes
  if (name_len >= 0x100)
    return -1;

  // Write length prefix
  if (name_len >= 0x20)
  {
    // Long string prefix (0xD9) followed by the length byte
    if (am_writechar(ctx, 0xD9) || am_writechar(ctx, (char)name_len))
      return -1;
  }
  else
  {
    // Short string prefix (0xA0 to 0xBF) encoding the length directly
    if (am_writechar(ctx, (char)(name_len + 0xA0)))
      return -1;
  }

  // Check if buffer has enough space, flush if necessary
  buf_len = ctx->p - ctx->buf;
  if (name_len + buf_len > 0x1000)
  {
    ctx->p = ctx->buf; // Reset buffer pointer
    if (buf_len)
    {
      write_ret = dumper->writer(dumper, ctx->buf, buf_len);
      ctx->ret = write_ret;
      if (write_ret)
        return -1;
    }
  }

  // Copy string to buffer and advance pointer
  memcpy(ctx->p, name, name_len);
  ctx->p += name_len;

  return 0;
}