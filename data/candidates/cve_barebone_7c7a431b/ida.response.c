void __cdecl RemoveICCProfileFromResourceBlock(StringInfo *bim_profile)
{
  bool v1; // [rsp+7h] [rbp-39h]
  unsigned __int8 *q; // [rsp+8h] [rbp-38h]
  unsigned __int16 short_sans; // [rsp+14h] [rbp-2Ch] BYREF
  unsigned __int16 id; // [rsp+16h] [rbp-2Ah] BYREF
  unsigned int long_sans; // [rsp+18h] [rbp-28h] BYREF
  unsigned int count; // [rsp+1Ch] [rbp-24h] BYREF
  unsigned __int8 *datum; // [rsp+20h] [rbp-20h]
  size_t length; // [rsp+28h] [rbp-18h]
  const unsigned __int8 *p; // [rsp+30h] [rbp-10h]
  StringInfo *bim_profilea; // [rsp+38h] [rbp-8h]

  bim_profilea = bim_profile;
  length = GetStringInfoLength(bim_profile);
  if ( length >= 0x10 )
  {
    datum = GetStringInfoDatum(bim_profilea);
    p = datum;
    while ( 1 )
    {
      v1 = 0;
      if ( p >= datum )
        v1 = p < &datum[length - 16];
      if ( !v1 )
        break;
      q = (unsigned __int8 *)p;
      if ( LocaleNCompare((const char *)p, "8BIM", 4uLL) )
        break;
      p = PushLongPixel(MSBEndian, p, &long_sans);
      p = PushShortPixel(MSBEndian, p, &id);
      p = PushShortPixel(MSBEndian, p, &short_sans);
      p = PushLongPixel(MSBEndian, p, &count);
      if ( id == 1039 )
      {
        CopyMagickMemory(
          q,
          &q[((count + 1LL) & 0xFFFFFFFFFFFFFFFELL) + 12],
          length - (((count + 1LL) & 0xFFFFFFFFFFFFFFFELL) + 12) - (q - datum));
        SetStringInfoLength(bim_profilea, length - (((count + 1LL) & 0xFFFFFFFFFFFFFFFELL) + 12));
        return;
      }
      p += count;
      if ( (count & 1) != 0 )
        ++p;
    }
  }
}