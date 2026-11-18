static int ImagingPcxDecode(ImagingVipsDecode *self,
                            ImagingVipsDecodePrivate *priv,
                            unsigned char *data, gsize length) {
  unsigned char *p;
  unsigned char count;
  int i;
  if (!strcmp(self->bits, "1") && priv->width * 8 < priv->rowstride) {
    priv->error = -1;
    return -1;
  }
  p = data;
  while (length >= 1) {
    if ((*p & 0xc0) == 0xc0) {
      if (length < 2) break;
      count = *p & 0x3f;
      while (count) {
        if (priv->rowpos >= priv->rowstride) {
          priv->error = -1;
          break;
        }
        priv->row[priv->rowpos++] = *(p + 1);
        count--;
      }
      p += 2;
      length -= 2;
    } else {
      priv->row[priv->rowpos++] = *p;
      p++;
      length--;
    }
    if (priv->rowpos >= priv->rowstride) {
      if (priv->rowstride % priv->width && priv->rowstride > priv->width) {
        int n = priv->rowstride / priv->width;
        int m = priv->rowstride / n;
        for (i = 1; i < n; i++)
          memmove(priv->row + i * priv->width, priv->row + i * m, priv->width);
      }
      priv->write_line(self->lines[priv->y][priv->plane] +
                           priv->x * self->bytes_per_sample,
                       priv->row, priv->width);
      priv->rowpos = 0;
      if (++priv->y >= priv->height) return -1;
    }
  }
  return p - data;
}