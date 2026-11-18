static enum GF_Err GF_AdobeBootstrapInfoBox_read(struct GF_Box *box, struct GF_BitStream *stream)
{
  struct GF_AdobeBootstrapInfoBox *thisBox = (GF_ADOBE_BOOTSTRAP_INFO_BOX *)box;
  if (thisBox->size < (unsigned long)(sizeof(GF_ADOBE_BOOTSTRAP_INFO_BOX)))
  {
    return -20;
  }
  thisBox->size -= (unsigned long)(sizeof(GF_ADOBE_BOOTSTRAP_INFO_BOX));
  thisBox->bootstrapinfo_version = GF_BitStream_Read(stream, 1);
  thisBox->profile = GF_BitStream_Read(stream, 2);
  thisBox->live = GF_BitStream_Read(stream, 1);
  thisBox->update = GF_BitStream_Read(stream, 1);
  thisBox->reserved = GF_BitStream_Read(stream, 4);
  thisBox->time_scale = GF_BitStream_Read(stream, 16);
  thisBox->current_media_time = GF_BitStream_Read(stream, 64);
  thisBox->smpte_time_code_offset = GF_BitStream_Read(stream, 64);
  int i = 0;
  if (thisBox->size < (unsigned long)(sizeof(char)))
  {
    return -20;
  }
  unsigned long tmp_strsize = thisBox->size - (unsigned long)(sizeof(char));
  char *tmp_str = (char *)GF_Alloc(tmp_strsize);
  if (tmp_str == ((void *)0))
  {
    return -2;
  }
  GF_Memset(tmp_str, 0, tmp_strsize);
  while (tmp_strsize > 0)
  {
    if (thisBox->size < (unsigned long)(sizeof(char)))
    {
      return -20;
    }
    thisBox->size -= (unsigned long)(sizeof(char));
    tmp_str[i] = GF_BitStream_Read(stream, 8);
    tmp_strsize -= (unsigned long)(sizeof(char));
    if (tmp_str[i] == 0)
    {
      break;
    }
    i++;
  }
  if (i > 0)
  {
    thisBox->movie_identifier = GF_Strndup(tmp_str, i);
  }
  if (thisBox->size < (unsigned long)(sizeof(char)))
  {
    return -20;
  }
  thisBox->size -= (unsigned long)(sizeof(char));
  thisBox->server_entry_count = GF_BitStream_Read(stream, 8);
  for (i = 0; i < thisBox->server_entry_count; i++)
  {
    int j = 0;
    tmp_strsize = thisBox->size;
    while (tmp_strsize > 0)
    {
      if (thisBox->size < (unsigned long)(sizeof(char)))
      {
        return -20;
      }
      thisBox->size -= (unsigned long)(sizeof(char));
      tmp_str[j] = GF_BitStream_Read(stream, 8);
      tmp_strsize -= (unsigned long)(sizeof(char));
      if (tmp_str[j] == 0)
      {
        break;
      }
      j++;
    }
    if (j > 0)
    {
      struct GF_List *server_entry_table = thisBox->server_entry_table;
      GF_List_Set(server_entry_table, GF_Strndup(tmp_str, j), i);
    }
  }
  if (thisBox->size < (unsigned long)(sizeof(char)))
  {
    return -20;
  }
  thisBox->size -= (unsigned long)(sizeof(char));
  thisBox->quality_entry_count = GF_BitStream_Read(stream, 8);
  for (i = 0; i < thisBox->quality_entry_count; i++)
  {
    int j = 0;
    tmp_strsize = thisBox->size;
    while (tmp_strsize > 0)
    {
      if (thisBox->size < (unsigned long)(sizeof(char)))
      {
        return -20;
      }
      thisBox->size -= (unsigned long)(sizeof(char));
      tmp_str[j] = GF_BitStream_Read(stream, 8);
      tmp_strsize -= (unsigned long)(sizeof(char));
      if (tmp_str[j] == 0)
      {
        break;
      }
      j++;
    }
    if (j > 0)
    {
      struct GF_List *quality_entry_table = thisBox->quality_entry_table;
      GF_List_Set(quality_entry_table, GF_Strndup(tmp_str, j), i);
    }
  }
  i = 0;
  tmp_strsize = thisBox->size;
  while (tmp_strsize > 0)
  {
    if (thisBox->size < (unsigned long)(sizeof(char)))
    {
      return -20;
    }
    thisBox->size -= (unsigned long)(sizeof(char));
    tmp_str[i] = GF_BitStream_Read(stream, 8);
    tmp_strsize -= (unsigned long)(sizeof(char));
    if (tmp_str[i] == 0)
    {
      break;
    }
    i++;
  }
  if (i > 0)
  {
    thisBox->drm_data = GF_Strndup(tmp_str, i);
  }
  i = 0;
  tmp_strsize = thisBox->size;
  while (tmp_strsize > 0)
  {
    if (thisBox->size < (unsigned long)(sizeof(char)))
    {
      return -20;
    }
    thisBox->size -= (unsigned long)(sizeof(char));
    tmp_str[i] = GF_BitStream_Read(stream, 8);
    tmp_strsize -= (unsigned long)(sizeof(char));
    if (tmp_str[i] == 0)
    {
      break;
    }
    i++;
  }
  if (i > 0)
  {
    thisBox->meta_data = GF_Strndup(tmp_str, i);
  }
  if (thisBox->size < (unsigned long)(sizeof(char)))
  {
    return -20;
  }
  thisBox->size -= (unsigned long)(sizeof(char));
  thisBox->segment_run_table_count = GF_BitStream_Read(stream, 8);
  for (i = 0; i < thisBox->segment_run_table_count; i++)
  {
    struct GF_AdobeSegmentRunTableBox *asrt = ((void *)0);
    enum GF_Err err = GF_Box_Read(&asrt, stream);
    if (err != (GF_Err))0)
    {
      if (asrt != ((void *)0))
      {
        do { QScopedPointerPodDeleter::cleanup((asrt)); } while (0);
      }
      GF_StrndupFree(tmp_str);
      return err;
    }
    GF_List_Add(thisBox->segment_run_table_entries, asrt);
  }
  if (thisBox->size < (unsigned long)(sizeof(char)))
  {
    return -20;
  }
  thisBox->size -= (unsigned long)(sizeof(char));
  unsigned char fragment_run_table_count = GF_BitStream_Read(stream, 8);
  for (i = 0; i < fragment_run_table_count; i++)
  {
    struct GF_AdobeFragmentRunTableBox *afrt = ((void *)0);
    enum GF_Err err = GF_Box_Read(&afrt, stream);
    if (err != (GF_Err))0)
    {
      if (afrt != ((void *)0))
      {
        do { QScopedPointerPodDeleter::cleanup((afrt)); } while (0);
      }
      GF_StrndupFree(tmp_str);
      return err;
    }
    GF_List_Add(thisBox->fragment_run_table_entries, afrt);
  }
  GF_StrndupFree(tmp_str);