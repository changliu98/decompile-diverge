void __cdecl print_udta(GF_ISOFile *file, u32 track_number, Bool has_itags)
{
  const char *v3; // rax
  struct _IO_FILE *stream; // [rsp+8h] [rbp-68h]
  u32 udta_size; // [rsp+14h] [rbp-5Ch] BYREF
  u8 *udta; // [rsp+18h] [rbp-58h] BYREF
  bin128 uuid_0; // [rsp+20h] [rbp-50h] BYREF
  u32 first; // [rsp+30h] [rbp-40h]
  u32 nb_items; // [rsp+34h] [rbp-3Ch]
  u32 type_0; // [rsp+38h] [rbp-38h] BYREF
  u32 j; // [rsp+3Ch] [rbp-34h]
  bin128 uuid; // [rsp+40h] [rbp-30h] BYREF
  u32 type; // [rsp+54h] [rbp-1Ch] BYREF
  u32 count; // [rsp+58h] [rbp-18h]
  u32 i; // [rsp+5Ch] [rbp-14h]
  Bool has_itagsa; // [rsp+60h] [rbp-10h]
  u32 track_numbera; // [rsp+64h] [rbp-Ch]
  GF_ISOFile *filea; // [rsp+68h] [rbp-8h]

  filea = file;
  track_numbera = track_number;
  has_itagsa = has_itags;
  count = gf_isom_get_udta_count(file, track_number);
  if ( count )
  {
    if ( has_itagsa == GF_FALSE )
      goto LABEL_9;
    for ( i = 0; i < count; ++i )
    {
      gf_isom_get_udta_type(filea, track_numbera, i + 1, &type, (bin128 *)uuid);
      if ( type == 1835365473 )
      {
        --count;
        break;
      }
    }
    if ( count )
    {
LABEL_9:
      fprintf(stderr, "%d UDTA types: ", count);
      for ( i = 0; i < count; ++i )
      {
        first = 1;
        gf_isom_get_udta_type(filea, track_numbera, i + 1, &type_0, (bin128 *)uuid_0);
        nb_items = gf_isom_get_user_data_count(filea, track_numbera, type_0, uuid_0);
        stream = stderr;
        v3 = gf_4cc_to_str(type_0);
        fprintf(stream, "%s (%d) ", v3, nb_items);
        for ( j = 0; j < nb_items; ++j )
        {
          udta = 0LL;
          gf_isom_get_user_data(filea, track_numbera, type_0, uuid_0, j + 1, &udta, &udta_size);
          if ( udta )
          {
            if ( gf_utf8_is_legal(udta, udta_size) )
            {
              if ( first )
              {
                fprintf(stderr, "\n");
                first = 0;
              }
              fprintf(stderr, "\t%s\n", (const char *)udta);
            }
            gf_free(udta);
          }
        }
      }
      fprintf(stderr, "\n");
    }
  }
}