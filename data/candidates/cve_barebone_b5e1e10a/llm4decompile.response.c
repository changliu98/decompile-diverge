void print_udta(GF_ISOFile *file, u32 track_number, Bool has_itags)
{
 u32 count, i, j, nb_items, type, udta_size;
 bin128 uuid;
 char *udta;
 Bool first;

 count = gf_isom_get_udta_count(file, track_number);
 if (!count) return;


 if (has_itags != GF_FALSE) {
  for (i = 0; i < count; i++) {
   gf_isom_get_udta_type(file, track_number, i+1, &type, &uuid);
   if (type == ((((u32)'m')<<24) | (((u32)'e')<<16) | (((u32)'t')<<8) | (((u32)'a')))) {
    count--;
    break;
   }
  }
  if (!count) return;
 }

 fprintf(PTR_stderr->stream, "%d UDTA types: ", count);
 for (i = 0; i < count; i++) {
  first = 1;
  gf_isom_get_udta_type(file, track_number, i+1, &type, &uuid);
  nb_items = gf_isom_get_user_data_count(file, track_number, type, uuid);
  fprintf(PTR_stderr->stream, "%s (%d) ", gf_4cc_to_str(type), nb_items);
  for (j = 0; j < nb_items; j++) {
   udta = NULL;
   gf_isom_get_user_data(file, track_number, type, uuid, j+1, (u8 **)&udta, &udta_size);
   if (udta) {
    if (gf_utf8_is_legal(udta, udta_size) != GF_FALSE) {
     if (first) {
      fprintf(PTR_stderr->stream, "\n");
      first = 0;
     }
     fprintf(PTR_stderr->stream, "\t%s\n", udta);
    }
    gf_free(udta);
   }
  }
 }
 fprintf(PTR_stderr->stream, "\n");
}