struct GF_Err abst_box_read(struct GF_Box *box, struct GF_BitStream *stream)
{
  struct GF_AdobeBootstrapInfoBox *abib = (GF_ADOBE_BOOTSTRAP_INFO_BOX*)box;
  if (abib->size < (sizeof(GF_ADOBE_BOOTSTRAP_INFO_BOX) - sizeof(GF_Box)))
    return (-20);
  abib->size -= (sizeof(GF_ADOBE_BOOTSTRAP_INFO_BOX) - sizeof(GF_Box));
  abib->bootstrapinfo_version = GF_ReadULong(stream);
  abib->profile = GF_ReadUShort(stream, 2);
  abib->live = GF_ReadUShort(stream, 1);
  abib->update = GF_ReadUShort(stream, 1);
  abib->reserved = GF_ReadUShort(stream, 4);
  abib->time_scale = GF_ReadULong(stream);
  abib->current_media_time = GF_ReadFixed(stream);
  abib->smpte_time_code_offset = GF_ReadFixed(stream);
  int i = 0;
  if (abib->size < 8)
    return (-20);
  unsigned int tmp_strsize = abib->size;
  char *tmp_str = (char *)GF_Alloc(tmp_strsize);
  if (tmp_str == ((void *)0))
    return (-2);
  GF_Memset(tmp_str, 0, tmp_strsize);
  while (tmp_strsize > 0)
  {
    if (abib->size < 1)
      return (-20);
    abib->size -= 1;
    tmp_str[i] = GF_ReadUByte(stream);
    tmp_strsize -= 1;
    if (tmp_str[i] == 0)
      break;
    i++;
  }
  if (i > 0)
    abib->movie_identifier = GF_Strndup(tmp_str);
  if (abib->size < 1)
    return (-20);
  abib->size -= 1;
  abib->server_entry_count = GF_ReadUByte(stream);
  for (i = 0; i < abib->server_entry_count; i++)
  {
    int j = 0;
    tmp_strsize = abib->size;
    while (tmp_strsize > 0)
    {
      if (abib->size < 1)
        return (-20);
      abib->size -= 1;
      tmp_str[j] = GF_ReadUByte(stream);
      tmp_strsize -= 1;
      if (tmp_str[j] == 0)
        break;
      j++;
    }
    if (j > 0)
      GF_ListAdd(abib->server_entry_table, GF_Strndup(tmp_str), i);
  }
  if (abib->size < 1)
    return (-20);
  abib->size -= 1;
  abib->quality_entry_count = GF_ReadUByte(stream);
  for (i = 0; i < abib->quality_entry_count; i++)
  {
    int j = 0;
    tmp_strsize = abib->size;
    while (tmp_strsize > 0)
    {
      if (abib->size < 1)
        return (-20);
      abib->size -= 1;
      tmp_str[j] = GF_ReadUByte(stream);
      tmp_strsize -= 1;
      if (tmp_str[j] == 0)
        break;
      j++;
    }
    if (j > 0)
      GF_ListAdd(abib->quality_entry_table, GF_Strndup(tmp_str), i);
  }
  i = 0;
  tmp_strsize = abib->size;
  while (tmp_strsize > 0)
  {
    if (abib->size < 1)
      return (-20);
    abib->size -= 1;
    tmp_str[i] = GF_ReadUByte(stream);
    tmp_strsize -= 1;
    if (tmp_str[i] == 0)
      break;
    i++;
  }
  if (i > 0)
    abib->drm_data = GF_Strndup(tmp_str);
  i = 0;
  tmp_strsize = abib->size;
  while (tmp_strsize > 0)
  {
    if (abib->size < 1)
      return (-20);
    abib->size -= 1;
    tmp_str[i] = GF_ReadUByte(stream);
    tmp_strsize -= 1;
    if (tmp_str[i] == 0)
      break;
    i++;
  }
  if (i > 0)
    abib->meta_data = GF_Strndup(tmp_str);
  if (abib->size < 1)
    return (-20);
  abib->size -= 1;
  abib->segment_run_table_count = GF_ReadUByte(stream);
  for (i = 0; i < abib->segment_run_table_count; i++)
  {
    struct GF_AdobeSegmentRunTableBox *asrt = ((void *)0);
    struct GF_Err e = GF_ReadBox((struct GF_Box **)&asrt, stream);
    if (e.id != (0))
    {
      if (asrt != ((void *)0))
        do { if (asrt) { QScopedPointerPodDeleter::cleanup((asrt)); (asrt) = ((void *)0); } } while (0);
      GF_Free(tmp_str);
      return e;
    }
    GF_ListAdd(abib->segment_run_table_entries, asrt);
  }
  if (abib->size < 1)
    return (-20);
  abib->size -= 1;
  unsigned char fragment_run_table_count = GF_ReadUByte(stream);
  for (i = 0; i < fragment_run_table_count; i++)
  {
    struct GF_AdobeFragmentRunTableBox *afrt = ((void *)0);
    struct GF_Err e = GF_ReadBox((struct GF_Box **)&afrt, stream);
    if (e.id != (0))
    {
      if (afrt != ((void *)0))
        do { if (afrt) { QScopedPointerPodDeleter::cleanup((afrt)); (afrt) = ((void *)0); } } while (0);
      GF_Free(tmp_str);
      return e;
    }
    GF_ListAdd(abib->fragment_run_table_entries, afrt);
  }
  GF_Free(tmp_str);
  return (0);
}