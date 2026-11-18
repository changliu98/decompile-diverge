OPJ_BOOL opj_j2k_add_tlmarker(OPJ_UINT32 tileno, opj_codestream_index_t *cstr_index, OPJ_UINT32 type, OPJ_OFF_T pos, OPJ_UINT32 len)
{
  if (cstr_index != ((void *)0))
  {
    if (cstr_index->tile_index != ((void *)0))
    {
      if (cstr_index->tile_index[tileno].marknum + 1 > cstr_index->tile_index[tileno].maxmarknum)
      {
        cstr_index->tile_index[tileno].maxmarknum =
          cstr_index->tile_index[tileno].maxmarknum + 100;
        opj_marker_info_t *new_marker = (opj_marker_info_t *)
          qstrcpy(cstr_index->tile_index[tileno].marker,
                  cstr_index->tile_index[tileno].maxmarknum * sizeof(opj_marker_info_t));
        if (new_marker == ((void *)0))
        {
          opj_free(cstr_index->tile_index[tileno].marker);
          cstr_index->tile_index[tileno].marker = ((void *)0);
          cstr_index->tile_index[tileno].maxmarknum = 0;
          cstr_index->tile_index[tileno].marknum = 0;
          return (OPJ_BOOL)(0);
        }
        cstr_index->tile_index[tileno].marker = new_marker;
      }
      cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].type = type;
      cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].pos = (OPJ_UINT32)pos;
      cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].len = len;
      cstr_index->tile_index[tileno].marknum++;
      if (type == (0x00010000 | 0x0001))
      {
        if (cstr_index->tile_index[tileno].tp_index != ((void *)0))
        {
          cstr_index->tile_index[tileno].tp_index[cstr_index->tile_index[tileno].current_tpsno].start_pos = (OPJ_UINT32)pos;
        }
      }
      return (OPJ_BOOL)(1);
    }
    else
    {
      do { if (cstr_index->tile_index != (0)) { printf("Assertion failed at line %d of %s: %s\n", 224, "/work/harness.c", "cstr_index->tile_index != 0"); exit(-1); } } while (0);
    }
  }
  else
  {
    do { if (cstr_index != (0)) { printf("Assertion failed at line %d of %s: %s\n", 223, "/work/harness.c", "cstr_index != 0"); exit(-1); } } while (0);
  }
  return (OPJ_BOOL)(0);
}