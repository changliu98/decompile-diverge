int __cdecl kwajd_read_headers(mspack_system *sys, mspack_file *fh, mskwajd_header *hdr)
{
  off_t pos;
  int i;
  char *fn;
  unsigned __int8 buf[16];

  // Read the 14-byte base header
  if (sys->read(fh, buf, 14) != 14)
    return 3; // MSPACK_ERR_READ

  // Verify magic signature: "KWAJ" (0x4A41574B) and variant marker (0x0D1271B8)
  if ((buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24)) != 0x4A41574B ||
      (buf[4] | (buf[5] << 8) | (buf[6] << 16) | (buf[7] << 24)) != 0xD1271B8)
  {
    return 7; // MSPACK_ERR_SIGNATURE
  }

  // Parse base header fields
  hdr->comp_type    = *(_WORD *)&buf[8];
  hdr->data_offset  = *(unsigned __int16 *)&buf[10];
  hdr->headers      = *(unsigned __int16 *)&buf[12];
  hdr->length       = 0LL;
  hdr->filename     = 0LL;
  hdr->extra        = 0LL;
  hdr->extra_length = 0;

  // Header flag 0x01: Uncompressed file length
  if ((hdr->headers & 0x01) != 0)
  {
    if (sys->read(fh, buf, 4) != 4)
      return 3;
    hdr->length = buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24);
  }

  // Header flag 0x02: Unknown 2-byte field
  if ((hdr->headers & 0x02) != 0)
  {
    if (sys->read(fh, buf, 2) != 2)
      return 3;
  }

  // Header flag 0x04: 2-byte data offset adjustment
  if ((hdr->headers & 0x04) != 0)
  {
    if (sys->read(fh, buf, 2) != 2)
      return 3;
    if (sys->seek(fh, *(unsigned __int16 *)buf, 1))
      return 5; // MSPACK_ERR_SEEK
  }

  // Header flags 0x08 & 0x10: Filename and extension
  if ((hdr->headers & 0x18) != 0)
  {
    pos = sys->tell(fh);
    fn = (char *)sys->alloc(sys, 13LL);
    if (!fn)
      return 6; // MSPACK_ERR_NOMEMORY
    
    hdr->filename = fn;

    // Flag 0x08: Read up to 9 bytes for the base filename
    if ((hdr->headers & 0x08) != 0)
    {
      if (sys->read(fh, buf, 9) != 9)
        return 3;
      
      for (i = 0; i < 9; ++i)
      {
        *fn = buf[i];
        if (!buf[i])
          break;
        ++fn;
      }
      
      pos += (i >= 9) ? 9 : (i + 1);
      if (sys->seek(fh, pos, 0))
        return 5;
    }

    // Flag 0x10: Read up to 4 bytes for the file extension
    if ((hdr->headers & 0x10) != 0)
    {
      *fn++ = '.'; // 46 == '.'
      
      if (sys->read(fh, buf, 4) != 4)
        return 3;
      
      for (i = 0; i < 4; ++i)
      {
        *fn = buf[i];
        if (!buf[i])
          break;
        ++fn;
      }
      
      if (sys->seek(fh, pos + ((i >= 4) ? 4 : (i + 1)), 0))
        return 5;
    }

    *fn = 0; // Null-terminate the filename string
  }

  // Header flag 0x20: Extra data block
  if ((hdr->headers & 0x20) != 0)
  {
    if (sys->read(fh, buf, 2) != 2)
      return 3;
    
    int extra_len = *(unsigned __int16 *)buf;
    hdr->extra = (char *)sys->alloc(sys, extra_len + 1LL);
    if (!hdr->extra)
      return 6;
    
    if (sys->read(fh, hdr->extra, extra_len) != extra_len)
      return 3;
    
    hdr->extra[extra_len] = 0;
    hdr->extra_length = extra_len;
  }

  return 0; // MSPACK_ERR_OK
}