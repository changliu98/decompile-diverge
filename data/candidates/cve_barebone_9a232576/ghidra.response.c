ut8 * parse_die(ut8 *buf,ut8 *buf_end,RzBinDwarfDebugInfo *info,RzBinDwarfAbbrevDecl *abbrev,
               RzBinDwarfCompUnitHdr *hdr,RzBinDwarfDie *die,ut8 *debug_str,size_t debug_str_len,
               _Bool big_endian)

{
  _Bool _Var1;
  RzBinDwarfAttrValue *pRVar2;
  char *value;
  char *name;
  RzBinDwarfAttrValue *attribute;
  ut64 line_info_offset;
  char *comp_dir;
  size_t i;
  _Bool big_endian_local;
  RzBinDwarfDie *die_local;
  RzBinDwarfCompUnitHdr *hdr_local;
  RzBinDwarfAbbrevDecl *abbrev_local;
  RzBinDwarfDebugInfo *info_local;
  ut8 *buf_end_local;
  ut8 *buf_local;
  
  comp_dir = (char *)0x0;
  line_info_offset = 0xffffffffffffffff;
  buf_local = buf;
  for (i = 0; i < abbrev->count - 1; i = i + 1) {
    memset(die->attr_values + i,0,0x28);
    buf_local = parse_attr_value(buf_local,(int)buf_end - (int)buf_local,abbrev->defs + i,
                                 die->attr_values + i,hdr,debug_str,debug_str_len,big_endian);
    pRVar2 = die->attr_values + i;
    if ((pRVar2->attr_name == 0x1b) &&
       (((pRVar2->attr_form == 0xe || (pRVar2->attr_form == 8)) && ((pRVar2->field_3).address != 0))
       )) {
      comp_dir = (pRVar2->field_3).string.content;
    }
    if (pRVar2->attr_name == 0x10) {
      if (pRVar2->kind == DW_AT_KIND_CONSTANT) {
        line_info_offset = (pRVar2->field_3).address;
      }
      else if (pRVar2->kind == DW_AT_KIND_REFERENCE) {
        line_info_offset = (pRVar2->field_3).address;
      }
    }
    die->count = die->count + 1;
  }
  if (((comp_dir != (char *)0x0) && (line_info_offset != 0xffffffffffffffff)) &&
     ((value = strdup(comp_dir), value != (char *)0x0 &&
      (_Var1 = ht_up_insert(info->line_info_offset_comp_dir,line_info_offset,value), !_Var1)))) {
    free(value);
  }
  return buf_local;
}