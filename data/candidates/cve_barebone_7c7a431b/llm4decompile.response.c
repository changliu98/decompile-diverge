void RemoveICCProfileFromResourceBlock(StringInfo *bim_profile)
{
  unsigned char
    *datum,
    *p,
    *q;

  unsigned int
    length,
    count;

  unsigned short
    id,
    short_sans;

  unsigned int
    long_sans;

  length=GetStringInfoLength(bim_profile);
  if (length < 16)
    return;
  datum=GetStringInfoDatum(bim_profile);
  p=datum;
  while ((p >= datum) && (p < (datum+(length-16))))
  {
    if (LocaleNCompare((char *) (p),("8BIM"),4) != 0)
      break;
    p=PushLongPixel(MSBEndian,p,&long_sans);
    p=PushShortPixel(MSBEndian,p,&id);
    p=PushShortPixel(MSBEndian,p,&short_sans);
    p=PushLongPixel(MSBEndian,p,&count);
    if (id == 0x040f)
      {
        q=p+count;
        if ((count & 0x01) != 0)
          q++;
        CopyMagickMemory(p,q,(size_t) (length-((size_t) (q-datum))));
        SetStringInfoLength(bim_profile,(size_t) (length-((size_t) (q-datum))));
        return;
      }
    p+=count;
    if ((count & 0x01) != 0)
      p++;
  }
}