u32 GetHintFormat(GF_TrackBox *trak)
{
 GF_HintMediaHeaderBox *hmhd = (GF_HintMediaHeaderBox *) trak->Media->information->InfoHeader;
 GF_Box *sd = NULL;
 u32 format;

 if (hmhd->type != 0x686D6864) return 0;

 if (hmhd && hmhd->maxPDUsize)
  return hmhd->maxPDUsize;

 sd = gf_list_get(trak->Media->information->sampleTable->SampleDescription->child_boxes, 0);

 if (hmhd) {
  if (sd) hmhd->maxPDUsize = sd->size;
  return hmhd->maxPDUsize;
 }

 format = sd ? sd->size : 0;
 return format;
}