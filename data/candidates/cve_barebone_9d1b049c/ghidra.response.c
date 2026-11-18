GF_Err Media_CheckDataEntry(GF_MediaBox *mdia,u32 dataEntryIndex)

{
  u32 uVar1;
  GF_Err e;
  GF_DataMap *map;
  GF_DataEntryURLBox *entry;
  u32 dataEntryIndex_local;
  GF_MediaBox *mdia_local;
  
  if (((mdia == (GF_MediaBox *)0x0) || (dataEntryIndex == 0)) ||
     (dataEntryIndex_local = dataEntryIndex, mdia_local = mdia,
     uVar1 = gf_list_count(mdia->information->dataInformation->dref->child_boxes),
     uVar1 < dataEntryIndex)) {
    return GF_BAD_PARAM;
  }
  entry = gf_list_get(mdia_local->information->dataInformation->dref->child_boxes,
                      dataEntryIndex_local - 1);
  if (entry == (GF_DataEntryURLBox *)0x0) {
    return GF_ISOM_INVALID_FILE;
  }
  if (entry->flags == 1) {
    return GF_OK;
  }
  if (entry->type == 0x75726e20) {
    return GF_NOT_SUPPORTED;
  }
  if (mdia_local->mediaTrack->moov->mov->openMode == GF_ISOM_OPEN_WRITE) {
    e = gf_isom_datamap_new(entry->location,(char *)0x0,'\x01',&map);
  }
  else {
    e = gf_isom_datamap_new(entry->location,mdia_local->mediaTrack->moov->mov->fileName,'\x01',&map)
    ;
  }
  if (e != GF_OK) {
    return e;
  }
  gf_isom_datamap_del(map);
  return GF_OK;
}