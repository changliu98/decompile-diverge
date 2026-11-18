static int _iso_open_data_reference(GF_ISOFile *isofile, u32 index)
{
 int status;
 GF_ISOMDataReferenceEntry *dref;
 GF_ISOMDataMap *datamap;
 unsigned int entry_index;

 if (!isofile || !index || index > gf_list_count(isofile->tracklist[1]->track->dataReferences))
  return -1;

 dref = (GF_ISOMDataReferenceEntry *)gf_list_get(isofile->tracklist[1]->track->dataReferences, index-1);
 if (!dref) return -20;

 if (dref->flags == 1)
  return 0;

 if (dref->data_reference_type == ((u32) (('r'<<24) | ('u'<<16) | ('n'<<8) | ' ')))
  return -4;

 if (isofile->tracklist[1]->track->track_type == 2)
  status = gf_isom_datamap_new(dref->data_reference, NULL, 1, &datamap);
 else
  status = gf_isom_datamap_new(dref->data_reference, isofile->tracklist[1]->track->file_name, 1, &datamap);

 if (status != 0)
 {
  return status;
 }
 else
 {
  gf_isom_datamap_del(datamap);
  return 0;
 }
}