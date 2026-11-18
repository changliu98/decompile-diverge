GF_Err __cdecl Media_CheckDataEntry(GF_MediaBox *mdia, u32 dataEntryIndex)
{
  GF_Err e; // [rsp+4h] [rbp-2Ch]
  GF_DataMap *map; // [rsp+8h] [rbp-28h] BYREF
  GF_DataEntryURLBox *entry; // [rsp+10h] [rbp-20h]
  u32 dataEntryIndexa; // [rsp+1Ch] [rbp-14h]
  GF_MediaBox *mdiaa; // [rsp+20h] [rbp-10h]

  mdiaa = mdia;
  dataEntryIndexa = dataEntryIndex;
  if ( !mdia
    || !dataEntryIndexa
    || dataEntryIndexa > gf_list_count(mdiaa->information->dataInformation->dref->child_boxes) )
  {
    return -1;
  }
  entry = (GF_DataEntryURLBox *)gf_list_get(mdiaa->information->dataInformation->dref->child_boxes, dataEntryIndexa - 1);
  if ( !entry )
    return -20;
  if ( entry->flags == 1 )
    return 0;
  if ( entry->type == 1970433568 )
    return -4;
  if ( mdiaa->mediaTrack->moov->mov->openMode == GF_ISOM_OPEN_WRITE )
    e = gf_isom_datamap_new(entry->location, 0LL, 1u, &map);
  else
    e = gf_isom_datamap_new(entry->location, mdiaa->mediaTrack->moov->mov->fileName, 1u, &map);
  if ( e )
    return e;
  gf_isom_datamap_del(map);
  return 0;
}