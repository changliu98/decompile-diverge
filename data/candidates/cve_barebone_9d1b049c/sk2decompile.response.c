static gf_int32_t Media_CheckDataEntry(MediaDataEntry *entry,
                                       unsigned int data_id) {
  gf_int32_t result;
  gf_isom_data_entry_t *data_entry;
  gf_isom_datamap_t *datamap;
  if (entry == NULL || data_id == 0 ||
      data_id > gf_list_count(entry->media->msnobj->msnfile->data_entries)) {
    return -1;
  }
  data_entry = (gf_isom_data_entry_t *)gf_list_get(
      entry->media->msnobj->msnfile->data_entries, data_id - 1);
  if (data_entry == NULL) {
    return -20;
  }
  if (data_entry->data_reference_id == 1) {
    return 0;
  }
  if (data_entry->data_type == 0x736f7570) {
    return -4;
  }
  if (entry->msnobj_entry->msn_entry->msn->type == MSN_TYPE_FRIEND) {
    result = gf_isom_datamap_new(data_entry->data_size, NULL, 1, &datamap);
  } else {
    result = gf_isom_datamap_new(
        data_entry->data_size,
        entry->msnobj_entry->msn_entry->msn->msn_key, 1, &datamap);
  }
  if (result != 0) {
    return result;
  }
  gf_isom_datamap_del(datamap);
  return 0;
}