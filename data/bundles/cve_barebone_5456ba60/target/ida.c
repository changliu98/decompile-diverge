int __cdecl kwajd_read_headers(mspack_system *sys, mspack_file *fh, mskwajd_header *hdr)
{
  unsigned __int8 v3; // al
  char *v4; // rax
  unsigned __int8 v5; // al
  char *v6; // rax
  int v8; // [rsp+0h] [rbp-50h]
  int v9; // [rsp+4h] [rbp-4Ch]
  char *fn; // [rsp+8h] [rbp-48h]
  off_t pos; // [rsp+10h] [rbp-40h]
  int i; // [rsp+1Ch] [rbp-34h]
  int ia; // [rsp+1Ch] [rbp-34h]
  int ib; // [rsp+1Ch] [rbp-34h]
  unsigned __int8 buf[16]; // [rsp+20h] [rbp-30h] BYREF
  mskwajd_header *hdra; // [rsp+30h] [rbp-20h]
  mspack_file *fha; // [rsp+38h] [rbp-18h]
  mspack_system *sysa; // [rsp+40h] [rbp-10h]

  sysa = sys;
  fha = fh;
  hdra = hdr;
  if ( sys->read(fh, buf, 14) != 14 )
    return 3;
  if ( (buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24)) != 1245796171
    || (buf[4] | (buf[5] << 8) | (buf[6] << 16) | (buf[7] << 24)) != -785911672 )
  {
    return 7;
  }
  hdra->comp_type = *(_WORD *)&buf[8];
  hdra->data_offset = *(unsigned __int16 *)&buf[10];
  hdra->headers = *(unsigned __int16 *)&buf[12];
  hdra->length = 0LL;
  hdra->filename = 0LL;
  hdra->extra = 0LL;
  hdra->extra_length = 0;
  if ( (hdra->headers & 1) != 0 )
  {
    if ( sysa->read(fha, buf, 4) != 4 )
      return 3;
    hdra->length = buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24);
  }
  if ( (hdra->headers & 2) == 0 || sysa->read(fha, buf, 2) == 2 )
  {
    if ( (hdra->headers & 4) != 0 )
    {
      if ( sysa->read(fha, buf, 2) != 2 )
        return 3;
      if ( sysa->seek(fha, *(unsigned __int16 *)buf, 1) )
        return 5;
    }
    if ( (hdra->headers & 0x18) != 0 )
    {
      pos = sysa->tell(fha);
      fn = (char *)sysa->alloc(sysa, 13LL);
      if ( !fn )
        return 6;
      hdra->filename = fn;
      if ( (hdra->headers & 8) != 0 )
      {
        if ( sysa->read(fha, buf, 9) != 9 )
          return 3;
        for ( i = 0; i < 9; ++i )
        {
          v3 = buf[i];
          *fn = v3;
          if ( !v3 )
            break;
          ++fn;
        }
        if ( i >= 9 )
          v9 = 9;
        else
          v9 = i + 1;
        pos += v9;
        if ( sysa->seek(fha, pos, 0) )
          return 5;
      }
      if ( (hdra->headers & 0x10) != 0 )
      {
        v4 = fn++;
        *v4 = 46;
        if ( sysa->read(fha, buf, 4) != 4 )
          return 3;
        for ( ia = 0; ia < 4; ++ia )
        {
          v5 = buf[ia];
          *fn = v5;
          if ( !v5 )
            break;
          ++fn;
        }
        if ( ia >= 4 )
          v8 = 4;
        else
          v8 = ia + 1;
        if ( sysa->seek(fha, pos + v8, 0) )
          return 5;
      }
      *fn = 0;
    }
    if ( (hdra->headers & 0x20) != 0 )
    {
      if ( sysa->read(fha, buf, 2) != 2 )
        return 3;
      ib = *(unsigned __int16 *)buf;
      v6 = (char *)sysa->alloc(sysa, *(unsigned __int16 *)buf + 1LL);
      hdra->extra = v6;
      if ( !hdra->extra )
        return 6;
      if ( sysa->read(fha, hdra->extra, ib) != ib )
        return 3;
      hdra->extra[ib] = 0;
      hdra->extra_length = ib;
    }
    return 0;
  }
  return 3;
}