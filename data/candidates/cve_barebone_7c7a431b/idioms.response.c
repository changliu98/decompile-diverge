void RemoveICCProfileFromResourceBlock(struct StringInfo *bim_profile)
{
  struct StringInfo *bim_profilea = bim_profile;
  unsigned long length = bim_getlength(bim_profile);
  if (length < 16)
    return;
  char *bim_data = bim_getdata(bim_profilea);
  char *bim_dataa = bim_data;
  for (;
       ((bim_dataa >= bim_data) && (bim_dataa < (bim_data + length - 16)));
       bim_dataa = bim_dataa + length)
  {
    char *bim_dataaa = bim_dataa;
    if (str_is(bim_dataaa, "8BIM", 4))
      break;
    unsigned int bim_data_len;
    unsigned short bim_data_id;
    unsigned short bim_data_subid;
    unsigned int bim_data_count;
    bim_dataa = bim_readlen(MSBEndian, bim_dataa, &bim_data_len);
    bim_dataa = bim_readid(MSBEndian, bim_dataa, &bim_data_id);
    bim_dataa = bim_readsubid(MSBEndian, bim_dataa, &bim_data_subid);
    bim_dataa = bim_readcount(MSBEndian, bim_dataa, &bim_data_count);
    if (bim_data_id == 1039)
    {
      char *bim_data_end = bim_dataaa + ((unsigned long)bim_data_count * (unsigned long)sizeof(char)) + 12;
      bim_readbim(bim_dataaa, bim_data_end, length - (bim_data_end - bim_dataaa));
      bim_setlength(bim_profilea, length - (bim_data_end - bim_dataaa));
      return;
    }
    bim_dataa = bim_dataaa + ((unsigned long)bim_data_count * (unsigned long)sizeof(char));
    if (bim_data_count & 1)
      bim_dataa++;
  }
}