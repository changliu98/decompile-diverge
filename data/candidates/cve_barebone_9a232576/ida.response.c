const ut8 *__cdecl parse_die(
        const ut8 *buf,
        const ut8 *buf_end,
        RzBinDwarfDebugInfo *info,
        RzBinDwarfAbbrevDecl *abbrev,
        RzBinDwarfCompUnitHdr *hdr,
        RzBinDwarfDie *die,
        const ut8 *debug_str,
        size_t debug_str_len,
        bool big_endian)
{
  char *name; // [rsp+10h] [rbp-60h]
  RzBinDwarfAttrValue *attribute; // [rsp+18h] [rbp-58h]
  ut64 line_info_offset; // [rsp+20h] [rbp-50h]
  const char *comp_dir; // [rsp+28h] [rbp-48h]
  size_t i; // [rsp+30h] [rbp-40h]

  comp_dir = 0LL;
  line_info_offset = -1LL;
  for ( i = 0LL; i < abbrev->count - 1; ++i )
  {
    memset(&die->attr_values[i], 0, sizeof(die->attr_values[i]));
    buf = parse_attr_value(
            buf,
            (int)buf_end - (int)buf,
            &abbrev->defs[i],
            &die->attr_values[i],
            hdr,
            debug_str,
            debug_str_len,
            big_endian);
    attribute = &die->attr_values[i];
    if ( attribute->attr_name == 27 && (attribute->attr_form == 14 || attribute->attr_form == 8) && attribute->address )
      comp_dir = attribute->string.content;
    if ( attribute->attr_name == 16 )
    {
      if ( attribute->kind == DW_AT_KIND_CONSTANT )
      {
        line_info_offset = attribute->address;
      }
      else if ( attribute->kind == DW_AT_KIND_REFERENCE )
      {
        line_info_offset = attribute->address;
      }
    }
    ++die->count;
  }
  if ( comp_dir )
  {
    if ( line_info_offset != -1LL )
    {
      name = strdup(comp_dir);
      if ( name )
      {
        if ( !ht_up_insert(info->line_info_offset_comp_dir, line_info_offset, name) )
          free(name);
      }
    }
  }
  return buf;
}