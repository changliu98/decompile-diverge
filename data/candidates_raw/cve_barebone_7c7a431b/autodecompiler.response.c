static void RemovePhotoshopProfile(StringInfo *profile)
{
  unsigned char
    *p;

  unsigned int
    id,
    length;

  long
    offset;

  short
    count;

  size_t
    size;

  ssize_t
    i;

  StringInfo
    *profile_info;

  unsigned char
    *q;

  size=GetStringInfoLength(profile);
  if (size < 17)
    return;
  profile_info=profile;
  p=GetStringInfoDatum(profile_info);
  q=p;
  for (i=size-16; i > 0; i--)
  {
    if ((q >= p) && (q < (p+size-16)))
      {
        q=(unsigned char *) q;
        if (LocaleNCompare((const char *) q,"8BIM",4) != 0)
          return;
        q=PushLongPixel(2,q,&offset);
        q=PushShortPixel(2,q,&id);
        q=PushShortPixel(2,q,&count);
        q=PushLongPixel(2,q,&length);
        if (id == 1039)
          {
            CopyMagickMemory(q,(q+((length+1) & ~1L)+12L),size-(12+((length+1) & ~1L))-(q-p));
            SetStringInfoLength(profile_info,size-(12+((length+1) & ~1L)));
            return;
          }
        q+=length;
        if ((length & 1) != 0)
          q++;
      }
  }
}