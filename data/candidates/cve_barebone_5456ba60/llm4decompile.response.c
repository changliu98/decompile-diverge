int kwajd_read_headers(mspack_system *sys, mspack_file *fh, mskwajd_header *hdr)
{
  unsigned char buf[16];
  int i, len;
  off_t pos;
  char *fn;


  if (sys->read(fh, buf, 14) != 14) {
    return 3;
  }


  if (((buf[0]) | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24)) != 0x4a41574b ||
      ((buf[4]) | (buf[5] << 8) | (buf[6] << 16) | (buf[7] << 24)) != 0xd127f088) {
    return 7;
  }


  hdr->comp_type = buf[8];
  hdr->data_offset = (buf[10]) | (buf[11] << 8);
  hdr->headers = (buf[12]) | (buf[13] << 8);
  hdr->length = 0;
  hdr->filename = NULL;
  hdr->extra = NULL;
  hdr->extra_length = 0;


  if (hdr->headers & 0x0001) {
    if (sys->read(fh, buf, 4) != 4) {
      return 3;
    }
    hdr->length = ((buf[0]) | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24));
  }


  if (hdr->headers & 0x0002) {
    if (sys->read(fh, buf, 2) != 2) {
      return 3;
    }
  }


  if (hdr->headers & 0x0004) {
    if (sys->read(fh, buf, 2) != 2) {
      return 3;
    }
    if (sys->seek(fh, (off_t) (buf[0]) | (buf[1] << 8), 1)) {
      return 5;
    }
  }


  if (hdr->headers & (0x0008 | 0x0010)) {
    pos = sys->tell(fh);
    if ((fn = (char *) sys->alloc(sys, 13)) == NULL) {
      return 6;
    }
    hdr->filename = fn;


    if (hdr->headers & 0x0008) {
      if (sys->read(fh, buf, 9) != 9) {
        return 3;
      }
      for (i = 0; i < 9 && (*fn++ = buf[i]); i++) ;
      pos += (i < 9) ? i + 1 : 9;
      if (sys->seek(fh, pos, 0)) {
        return 5;
      }
    }


    if (hdr->headers & 0x0010) {
      *fn++ = '.';
      if (sys->read(fh, buf, 4) != 4) {
        return 3;
      }
      for (i = 0; i < 4 && (*fn++ = buf[i]); i++) ;
      pos += (i < 4) ? i + 1 : 4;
      if (sys->seek(fh, pos, 0)) {
        return 5;
      }
    }


    *fn = '\0';
  }


  if (hdr->headers & 0x0020) {
    if (sys->read(fh, buf, 2) != 2) {
      return 3;
    }
    len = (buf[0]) | (buf[1] << 8);
    if ((hdr->extra = (char *) sys->alloc(sys, len + 1)) == NULL) {
      return 6;
    }
    if (sys->read(fh, hdr->extra, len) != len) {
      return 3;
    }
    hdr->extra[len] = '\0';
    hdr->extra_length = len;
  }

  return 0;
}