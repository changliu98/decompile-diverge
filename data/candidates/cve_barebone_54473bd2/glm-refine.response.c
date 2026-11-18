int __cdecl NeXTDecode(TIFF *tif, uint8 *buf, tmsize_t occ, uint16 s)
{
  tmsize_t occa = occ;
  uint8 *op = buf;
  tmsize_t cc = occ;

  // Fill the output buffer with 0xFF
  while (cc-- > 0)
    *op++ = 0xFF;

  uint8 *bp = tif->tif_rawcp;
  tmsize_t cca = tif->tif_rawcc;
  tmsize_t scanline = tif->tif_scanlinesize;

  if (occ % scanline != 0)
  {
    TIFFErrorExt(tif->tif_clientdata, "NeXTDecode", "Fractional scanlines cannot be read");
    return 0;
  }

  for (uint8 *row = buf; occa > 0; row += scanline)
  {
    if (cca <= 0 || occa <= 0)
    {
      tif->tif_rawcp = bp;
      tif->tif_rawcc = cca;
      return 1;
    }

    uint8 n = *bp++;
    cca--;

    if (n == 0)
    {
      // Case 1: Uncompressed scanline
      if (cca < scanline)
        goto bad;

      memcpy(row, bp, scanline);
      bp += scanline;
      cca -= scanline;
    }
    else if (n == 64)
    {
      // Case 2: Delta encoded scanline
      if (cca < 4)
        goto bad;

      tmsize_t off = bp[1] + (bp[0] << 8);
      tmsize_t na = bp[3] + (bp[2] << 8);

      if (cca < na + 4 || na + off > scanline)
        goto bad;

      memcpy(&row[off], bp + 4, na);
      bp += na + 4;
      cca -= na + 4;
    }
    else
    {
      // Case 3: Run-length encoded scanline
      uint32 npixels = 0;
      uint32 imagewidth = tif->tif_dir.td_imagewidth;
      
      if ((tif->tif_flags & 0x400) != 0)
        imagewidth = tif->tif_dir.td_tilewidth;

      uint8 *opa = row;
      while (npixels < imagewidth)
      {
        uint8 grey = (n >> 6) & 3;
        uint8 nb = n & 0x3F;

        while (nb-- > 0 && npixels < imagewidth)
        {
          uint8 mask = npixels & 3;
          if (mask == 0)
            *opa = grey << 6;
          else if (mask == 1)
            *opa |= grey << 4;
          else if (mask == 2)
            *opa |= grey << 2;
          else if (mask == 3)
            *opa++ |= grey;

          npixels++;
        }

        if (npixels >= imagewidth)
          break;

        if (cca == 0)
          goto bad;

        n = *bp++;
        cca--;
      }
    }

    occa -= scanline;
  }

  return 1;

bad:
  TIFFErrorExt(tif->tif_clientdata, "NeXTDecode", "Not enough data for scanline %ld", tif->tif_row);
  return 0;
}