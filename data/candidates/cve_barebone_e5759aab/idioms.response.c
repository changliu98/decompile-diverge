static _Bool opj_j2k_add_tlmarker(unsigned int tileno, struct opj_codestream_index *cstr_index, unsigned int type, long pos, unsigned int len)
{
  if (cstr_index != (struct opj_codestream_index *)((void *)0))
  {
    if (cstr_index->tile_index != (struct opj_tile_index *)((void *)0))
    {
      if (cstr_index->tile_index[tileno].marknum + 1 >
          cstr_index->tile_index[tileno].maxmarknum)
      {
        cstr_index->tile_index[tileno].maxmarknum =
          cstr_index->tile_index[tileno].maxmarknum + 100;
        struct opj_marker_info *new_marker = (opj_marker_info_t *)
          qstrcpy(cstr_index->tile_index[tileno].marker,
                  cstr_index->tile_index[tileno].maxmarknum *
                  sizeof(opj_marker_info_t));
        if (new_marker == ((void *)0))
        {
          opj_free(cstr_index->tile_index[tileno].marker);
          cstr_index->tile_index[tileno].marker = ((void *)0);
          cstr_index->tile_index[tileno].maxmarknum = 0;
          cstr_index->tile_index[tileno].marknum = 0;
          return 0;
        }
        cstr_index->tile_index[tileno].marker = new_marker;
      }
      cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].type = type;
      cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].pos = (unsigned int)pos;
      cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].len = len;
      cstr_index->tile_index[tileno].marknum++;
      if (type == 0xff00 &&
          cstr_index->tile_index[tileno].tp_index != ((void *)0))
      {
        cstr_index->tile_index[tileno].tp_index[cstr_index->tile_index[tileno].current_tpsno].start_pos = (unsigned int)pos;
      }
      return 1;
    }
  }
  opj_assert("cstr_index->tile_index != 00", "/work/harness.c", 106,
    "OPJ_BOOL opj_j2k_add_tlmarker(OPJ_UINT32, opj_codestream_index_t *, OPJ_UINT32, OPJ_OFF_T, OPJ_UINT32)");
  return 0;
}