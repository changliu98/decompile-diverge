GF_Err Media_CheckDataEntry(GF_MediaBox *mdia, u32 dataEntryIndex)
{
 GF_Err e;
 GF_DataEntryURLBox *entry;
 GF_DataMap *map;

 if (!mdia || !dataEntryIndex || dataEntryIndex > gf_list_count(mdia->information->dataInformation->dref->child_boxes))
  return GF_BAD_PARAM;

 entry = (GF_DataEntryURLBox *) gf_list_get(mdia->information->dataInformation->dref->child_boxes, dataEntryIndex - 1);
 if (!entry)
  return GF_ISOM_INVALID_FILE;


 if (entry->flags == 1)
  return GF_OK;


 if (entry->type == ( ((u32)'u') | ( ((u32)'r') << 8 ) | ( ((u32)'n') << 16 ) | ( ((u32)' ') << 24 ) ) )
  return GF_NOT_SUPPORTED;


 if (mdia->mediaTrack->moov->mov->openMode == GF_ISOM_OPEN_WRITE)
  e = gf_isom_datamap_new(entry->location, NULL, 1, &map);
 else
  e = gf_isom_datamap_new(entry->location, mdia->mediaTrack->moov->mov->fileName, 1, &map);

 if (e != GF_OK)
  return e;

 gf_isom_datamap_del(map);
 return GF_OK;
}