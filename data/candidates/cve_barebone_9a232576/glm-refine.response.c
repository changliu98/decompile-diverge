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
  char *name;
  RzBinDwarfAttrValue *attribute;
  ut64 line_info_offset;
  const char *comp_dir;
  size_t i;

  comp_dir = NULL;
  line_info_offset = (ut64)-1; // -1LL

  for ( i = 0LL; i < abbrev->count - 1; ++i )
  {
    memset(&die->attr_values[i], 0, sizeof(die->attr_values[i]));
    
    // Fixed 32-bit truncation cast from IDA decompilation to proper pointer diff
    buf = parse_attr_value(
            buf,
            (size_t)(buf_end - buf),
            &abbrev->defs[i],
            &die->attr_values[i],
            hdr,
            debug_str,
            debug_str_len,
            big_endian);
            
    attribute = &die->attr_values[i];
    
    // DW_AT_comp_dir (27) with DW_FORM_strp (14) or DW_FORM_string (8)
    if ( attribute->attr_name == DW_AT_comp_dir 
      && (attribute->attr_form == DW_FORM_strp || attribute->attr_form == DW_FORM_string) 
      && attribute->address )
    {
      comp_dir = attribute->string.content;
    }
    
    // DW_AT_stmt_list (16)
    if ( attribute->attr_name == DW_AT_stmt_list )
    {
      if ( attribute->kind == DW_AT_KIND_CONSTANT || attribute->kind == DW_AT_KIND_REFERENCE )
      {
        line_info_offset = attribute->address;
      }
    }
    
    ++die->count;
  }
  
  if ( comp_dir && line_info_offset != (ut64)-1 )
  {
    name = strdup(comp_dir);
    if ( name )
    {
      if ( !ht_up_insert(info->line_info_offset_comp_dir, line_info_offset, name) )
        free(name);
    }
  }
  
  return buf;
}