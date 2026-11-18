ut8 *parse_die(ut8 *buf, ut8 *buf_end, RzBinDwarfDebugInfo *info, RzBinDwarfAbbrevDecl *abbrev,
        RzBinDwarfCompUnitHdr *hdr, RzBinDwarfDie *die, const char *debug_str, size_t debug_str_len,
        bool big_endian) {
    const char *comp_dir = NULL;
    ut64 line_info_offset = ((ut64)-1);
    for (size_t i = 0; i < abbrev->count - 1; i++) {
        memset (&die->attr_values[i], 0, sizeof (RzBinDwarfAttrValue));
        buf = parse_attr_value (buf, buf_end - buf, &abbrev->defs[i], &die->attr_values[i],
                hdr, debug_str, debug_str_len, big_endian);
        if (die->attr_values[i].attr_name == 0x1b &&
                (die->attr_values[i].attr_form == 0x0e ||
                 die->attr_values[i].attr_form == 0x08) &&
                die->attr_values[i].value.string.content) {
            comp_dir = die->attr_values[i].value.string.content;
        }
        if (die->attr_values[i].attr_name == 0x10) {
            if (die->attr_values[i].kind == DW_AT_KIND_CONSTANT) {
                line_info_offset = die->attr_values[i].value.address;
            } else if (die->attr_values[i].kind == DW_AT_KIND_REFERENCE) {
                line_info_offset = die->attr_values[i].value.address;
            }
        }
        die->count++;
    }
    if (comp_dir && line_info_offset != ((ut64)-1)) {
        char *value = strdup (comp_dir);
        if (value) {
            if (!ht_up_insert (info->line_info_offset_comp_dir, line_info_offset, value)) {
                free (value);
            }
        }
    }
    return buf;
}