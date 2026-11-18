static void dump_udta(GF_ISOFile *isofile, u32 track, int itags)
{
 u32 i, j, count, nb_items;
 u32 type, type2;
 char *data;
 u32 data_size;
 GF_UUID uuid, uuid2;
 FILE *out;

 count = gf_isom_get_udta_count(isofile, track);
 if (!count) return;

 if (itags) {
  for (i=0; i<count; i++) {
   if (i>=count) break;
   gf_isom_get_udta_type(isofile, track, i+1, &type2, &uuid2);
   if (type2==0x6d657461) count--;
   else continue;
  }
  if (!count) return;
 } else {
  fprintf(stderr, "%d UDTA types: ", count);
 }

 for (i=0; i<count; i++) {
  int first = 1;
  gf_isom_get_udta_type(isofile, track, i+1, &type, &uuid);
  nb_items = gf_isom_get_user_data_count(isofile, track, type, &uuid);

  out = stderr;
  fprintf(out, "%s (%d) ", gf_4cc_to_str(type), nb_items);

  for (j=0; j<nb_items; j++) {
   data = NULL;
   gf_isom_get_user_data(isofile, track, type, &uuid, j+1, &data, &data_size);
   if (!data) continue;

   if (gf_utf8_is_legal(data, data_size)) {
    if (first) {
     fprintf(stderr, "\n");
     first = 0;
    }
    fprintf(stderr, "\t%s\n", data);
   }
   gf_free(data);
  }
 }
 fprintf(stderr, "\n");
}