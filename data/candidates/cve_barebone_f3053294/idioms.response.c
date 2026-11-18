char *utf_16le_to_utf_8_truncated(unsigned int *in, char *out, unsigned long outlen)
{
  char *outpos = out;
  unsigned long outleft = outlen;
  unsigned int u; unsigned int u2;
  if (outleft == 0)
    return out;
  while ((u = *in++)) {
    if (u >= 0xd800 && u <= 0xdfff) {
      u2 = *in;
      if (u2 == 0) {
        u = 0xfffd;
      } else {
        in++;
        if (u2 < 0xdc00 || u2 > 0xdfff)
          u = 0xfffd;
        else
          u = ((u - 0xd800) << 10) + (u2 - 0xdc00) + 0x00010000;
      }
    } else if (u >= 0xdc00 && u <= 0xdfff) {
      u = 0xfffd;
    }
    if (u < 0x80) {
      if (outleft < 2)
        break;
      *outpos++ = (char)u;
      outleft--;
    } else if (u < 0x800) {
      if (outleft < 3)
        break;
      *outpos++ = (char)((u >> 6) & 0x1f) | 0xc0;
      *outpos++ = (char)(u & 0x3f) | 0x80;
      outleft -= 2;
    } else if (u < 0x10000) {
      if (outleft < 4)
        break;
      *outpos++ = (char)((u >> 12) & 0xf) | 0xe0;
      *outpos++ = (char)((u >> 6) & 0x3f) | 0x80;
      *outpos++ = (char)(u & 0x3f) | 0x80;
      outleft -= 3;
    } else {
      if (outleft < 5)
        break;
      *outpos++ = (char)((u >> 18) & 0x7) | 0xf0;
      *outpos++ = (char)((u >> 12) & 0x3f) | 0x80;
      *outpos++ = (char)((u >> 6) & 0x3f) | 0x80;
      *outpos++ = (char)(u & 0x3f) | 0x80;
      outleft -= 3;
    }
  }
  *outpos = '\0';
  return outpos;
}