int NeXTDecode(struct tiff *tif, unsigned char *buf, unsigned long occ, unsigned short s)
{
  unsigned char *bp;
  unsigned char *op;
  unsigned long cc;
  unsigned long n;
  unsigned long off;
  unsigned long na;
  unsigned long npixels;
  unsigned int imagewidth;
  unsigned int grey;
  unsigned int i;
  unsigned char *row;
  unsigned char *opa;
  unsigned long scanline;
  int ok;
  int docopy;
  if (occ % tif->tif_scanlinesize != 0)
  {
    TIFFError(tif->tif_clientdata, "NeXTDecode",
      "Fractional scanlines cannot be read");
    return (0);
  }
  op = buf;
  cc = occ;
  while (cc-- > 0)
    *op++ = 0xff;
  bp = tif->tif_rawcp;
  cc = tif->tif_rawcc;
  scanline = tif->tif_scanlinesize;
  for (row = buf;;)
  {
    docopy = (cc > 0 && occ > 0);
    if (!docopy)
      break;
    n = *bp++;
    cc--;
    if (n == 0)
    {
      if (cc < scanline)
        goto bad;
      std::allocator_traits<std::allocator<std::__tree_node<std::__value_type<unsigned short,_IO_FILE *>,void *>>>::deallocate((std::tree<std::__value_type<unsigned short,_IO_FILE *>,std::allocator<std::__value_type<unsigned short,_IO_FILE *>>>::node *) (row), (unsigned long) (bp), (unsigned long) (scanline));
      bp += scanline;
      cc -= scanline;
    }
    else if (n == 64)
    {
      if (cc < 4 ||
        (off = bp[1] + (bp[0] << 8),
        na = bp[3] + (bp[2] << 8),
        cc < (na + 4) ||
        na + off > scanline))
        goto bad;
      std::allocator_traits<std::allocator<std::__tree_node<std::__value_type<unsigned short,_IO_FILE *>,void *>>>::deallocate((std::tree<std::__value_type<unsigned short,_IO_FILE *>,std::allocator<std::__value_type<unsigned short,_IO_FILE *>>>::node *) (row + off), (unsigned long) (bp + 4), (unsigned long) (na));
      bp += (na + 4);
      cc -= (na + 4);
    }
    else
    {
      npixels = 0;
      imagewidth = tif->tif_dir.td_imagewidth;
      if (tif->tif_flags & 0x00000040)
        imagewidth = tif->tif_dir.td_tilewidth;
      opa = row;
      for (;;)
      {
        grey = (n >> 6) & 0x03;
        na = n & 0x3f;
        for (i = na--; i > 0 && npixels < imagewidth;)
        {
          switch (npixels++ & 0x03)
          {
            case 0:
              *opa = (unsigned char) ((grey << 6) & 0xc0);
              break;
            case 1:
              *opa = (unsigned char) ((grey << 4) & 0x30);
              break;
            case 2:
              *opa = (unsigned char) ((grey << 2) & 0x0c);
              break;
            case 3:
              *opa = (unsigned char) (grey & 0x03);
              opa++;
              break;
          }
        }
        if (npixels >= imagewidth)
          break;
        if (cc < 1)
          goto bad;
        n = *bp++;
        cc--;
      }
    }
    occ -= scanline;
  }
  tif->tif_rawcp = bp;
  tif->tif_rawcc = cc;
  return (1);
 bad:
  TIFFError(tif->tif_clientdata, "NeXTDecode",
    "Not enough data for scanline %ld", tif->tif_row);
  return (0);
}