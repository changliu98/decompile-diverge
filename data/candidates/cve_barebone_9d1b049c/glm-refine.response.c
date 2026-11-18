GF_Err __cdecl Media_CheckDataEntry(GF_MediaBox *mdia, u32 dataEntryIndex)
{
  GF_Err e;
  GF_DataMap *map;
  GF_DataEntryURLBox *entry;
  GF_ISOFile *mov;

  // 1. Validate input arguments and bounds check against the number of child boxes in 'dref'
  if (!mdia || !dataEntryIndex || 
      dataEntryIndex > gf_list_count(mdia->information->dataInformation->dref->child_boxes))
  {
    return GF_BAD_PARAM; // -1
  }

  // 2. Retrieve the data entry URL box (1-based index to 0-based)
  entry = (GF_DataEntryURLBox *)gf_list_get(mdia->information->dataInformation->dref->child_boxes, 
                                            dataEntryIndex - 1);
  if (!entry)
    return GF_ISOM_INVALID_FILE; // -20

  // 3. If the flag indicates the data is self-contained (in the same file), return success
  if (entry->flags == 1)
    return GF_OK; // 0

  // 4. Check if the entry type is 'url ' (0x75726C20)
  if (entry->type == 0x75726C20) // 1970433568 decimal
    return GF_ISOM_INVALID_MODE; // -4

  mov = mdia->mediaTrack->moov->mov;

  // 5. Initialize a new data map depending on the open mode
  if (mov->openMode == GF_ISOM_OPEN_WRITE)
    e = gf_isom_datamap_new(entry->location, NULL, 1u, &map);
  else
    e = gf_isom_datamap_new(entry->location, mov->fileName, 1u, &map);

  // 6. If data map initialization failed, return the error
  if (e)
    return e;

  // 7. Clean up the data map and return success
  gf_isom_datamap_del(map);
  return GF_OK; // 0
}