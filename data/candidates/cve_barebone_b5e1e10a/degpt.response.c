void print_udta(GF_ISOFile *file,u32 track_number,Bool has_itags)

{
  FILE *__stream;
  bool bVar1;
  u32 uVar2;
  Bool BVar3;
  char *pcVar4;
  u32 udta_size;
  u8 *udta;
  bin128 uuid_1;
  u32 first;
  u32 nb_items;
  u32 type_1;
  u32 j;
  bin128 uuid;
  u32 type;
  u32 count;
  u32 i;
  Bool has_itags_local;
  u32 track_number_local;
  GF_ISOFile *file_local;
  
  has_itags_local = has_itags;
  track_number_local = track_number;
  file_local = file;
  count = gf_isom_get_udta_count(file,track_number);
  if (count != 0) {
    if (has_itags_local != GF_FALSE) {
      for (i = 0; i < count; i = i + 1) {
        gf_isom_get_udta_type(file_local,track_number_local,i + 1,&type,&uuid);
        if (type == 0x6d657461) {
          count = count - 1;
          break;
        }
      }
      if (count == 0) {
        return;
      }
    }
    fprintf(*(FILE **)PTR_stderr_00103ff8,"%d UDTA types: ",(ulong)count);
    for (i = 0; i < count; i = i + 1) {
      bVar1 = true;
      gf_isom_get_udta_type(file_local,track_number_local,i + 1,&type_1,&uuid_1);
      uVar2 = gf_isom_get_user_data_count(file_local,track_number_local,type_1,uuid_1);
      __stream = *(FILE **)PTR_stderr_00103ff8;
      pcVar4 = gf_4cc_to_str(type_1);
      fprintf(__stream,"%s (%d) ",pcVar4,(ulong)uVar2);
      for (j = 0; j < uVar2; j = j + 1) {
        udta = (u8 *)0x0;
        gf_isom_get_user_data(file_local,track_number_local,type_1,uuid_1,j + 1,&udta,&udta_size);
        if (udta != (u8 *)0x0) {
          BVar3 = gf_utf8_is_legal(udta,udta_size);
          if (BVar3 != GF_FALSE) {
            if (bVar1) {
              fprintf(*(FILE **)PTR_stderr_00103ff8,"\n");
              bVar1 = false;
            }
            fprintf(*(FILE **)PTR_stderr_00103ff8,"\t%s\n",udta);
          }
          gf_free(udta);
        }
      }
    }
    fprintf(*(FILE **)PTR_stderr_00103ff8,"\n");
  }
  return;
}