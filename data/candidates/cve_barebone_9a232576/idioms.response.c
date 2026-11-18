static char *parse_die(char *abbrev_data, char *abbrev_data_end, struct RzBinDwarfDebugInfo *info, struct RzBinDwarfAbbrevDecl *abbrev, struct RzBinDwarfCompUnitHdr *hdr, struct RzBinDwarfDie *die, char *debug_str, unsigned long debug_str_len, int big_endian)
{
  char *comp_dir = ((void *)0);
  char *line_info_comp_dir = ((void *)0);
  unsigned long i;
  for (i = 0; i < abbrev->count - 1; i++)
  {
    struct RzBinDwarfAttrValue *attr = &die->attr_values[i];
    rz_bin_dwarf_attr_value_init (die->attr_values + i, 0, sizeof (die->attr_values[i]));
    abbrev_data = read_abbrev_die_attr (abbrev_data,
        abbrev_data_end - abbrev_data,
        abbrev->defs + i,
        die->attr_values + i,
        hdr,
        debug_str,
        debug_str_len,
        big_endian);
    attr = die->attr_values + i;
    if (attr->attr_name == DW_AT_comp_dir &&
        (attr->attr_form == DW_FORM_string ||
         attr->attr_form == DW_FORM_data2) &&
        attr->address != 0)
    {
      comp_dir = attr->string.content;
    }
    if (attr->attr_name == DW_AT_line_base &&
        attr->kind == DW_AT_KIND_CONSTANT &&
        attr->address != 0)
    {
      line_info_comp_dir = (char *)attr->address;
    }
    if (attr->attr_name == DW_AT_line_base &&
        attr->kind == DW_AT_KIND_REFERENCE &&
        attr->address != 0)
    {
      line_info_comp_dir = (char *)attr->address;
    }
    die->count++;
  }
  if (comp_dir != ((void *)0) && line_info_comp_dir != ((void *)0))
  {
    char *line_info_comp_dir_name = get_line_info_comp_dir_name (comp_dir);
    if (line_info_comp_dir_name != ((void *)0))
    {
      if (!add_line_info_comp_dir (info->line_info_offset_comp_dir,
                                    line_info_comp_dir,
                                    line_info_comp_dir_name))
      {
        free_line_info_comp_dir_name (line_info_comp_dir_name);
      }
    }
  }
  return abbrev_data;
}