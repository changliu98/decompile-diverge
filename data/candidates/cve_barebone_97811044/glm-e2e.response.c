void iwjpeg_scan_exif_ifd(struct exif_info *info, struct exif_state *state, unsigned int offset) {
    int int_val;
    double dbl_val;
    unsigned int num_entries;
    unsigned int entry_offset;
    unsigned int tag;
    unsigned int i;

    // Bounds check: offset must be >= 8 and <= length - 18
    if (offset < 8 || offset > state->length - 18) {
        return;
    }

    // Read number of IFD entries
    num_entries = iw_get_ui16_e(state->data + offset, state->byte_order);
    if (num_entries > 1000) {
        return;
    }

    // Iterate over entries
    for (i = 0; i < num_entries; i++) {
        entry_offset = offset + 2 + i * 12;

        // Bounds check for the end of the current 12-byte entry
        if (entry_offset + 12 > state->length) {
            return;
        }

        // Read tag ID
        tag = iw_get_ui16_e(state->data + entry_offset, state->byte_order);

        // Switch on tag ID (using jump table)
        switch (tag) {
            case 0x0100: // 256: ImageWidth
                if (get_exif_tag_int_value(state, entry_offset, &int_val)) {
                    info->field_34 = int_val;
                }
                break;
            case 0x011a: // 282: XResolution
                if (get_exif_tag_dbl_value(state, entry_offset, &dbl_val)) {
                    info->field_38 = dbl_val;
                }
                break;
            case 0x011b: // 283: YResolution
                if (get_exif_tag_dbl_value(state, entry_offset, &dbl_val)) {
                    info->field_40 = dbl_val;
                }
                break;
            case 0x0128: // 296: ResolutionUnit
                if (get_exif_tag_int_value(state, entry_offset, &int_val)) {
                    info->field_48 = int_val;
                }
                break;
            default:
                break;
        }
    }
}