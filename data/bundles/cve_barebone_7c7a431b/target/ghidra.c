void RemoveICCProfileFromResourceBlock(StringInfo *bim_profile)

{
  uchar *destination;
  int iVar1;
  uchar *q;
  unsigned_short short_sans;
  unsigned_short id;
  uint long_sans;
  uint count;
  uchar *datum;
  size_t length;
  uchar *p;
  StringInfo *bim_profile_local;
  
  bim_profile_local = bim_profile;
  length = GetStringInfoLength(bim_profile);
  if (0xf < length) {
    datum = GetStringInfoDatum(bim_profile_local);
    p = datum;
    while( true ) {
      destination = p;
      if (p < datum || datum + (length - 0x10) <= p) {
        return;
      }
      iVar1 = LocaleNCompare((char *)p,"8BIM",4);
      if (iVar1 != 0) {
        return;
      }
      p = PushLongPixel(MSBEndian,p,&long_sans);
      p = PushShortPixel(MSBEndian,p,&id);
      p = PushShortPixel(MSBEndian,p,&short_sans);
      p = PushLongPixel(MSBEndian,p,&count);
      if (id == 0x40f) break;
      p = p + count;
      if ((count & 1) != 0) {
        p = p + 1;
      }
    }
    CopyMagickMemory(destination,destination + ((ulong)count + 1 & 0xfffffffffffffffe) + 0xc,
                     (length - (((ulong)count + 1 & 0xfffffffffffffffe) + 0xc)) -
                     ((long)destination - (long)datum));
    SetStringInfoLength(bim_profile_local,length - (((ulong)count + 1 & 0xfffffffffffffffe) + 0xc));
  }
  return;
}