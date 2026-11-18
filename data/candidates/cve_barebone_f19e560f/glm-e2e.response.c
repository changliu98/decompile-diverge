void iwjpeg_scan_exif_ifd(struct exif_results *res, struct exif_state *state, uint32_t ifd_offset) {
    // Check if offset is less than 8 or if it exceeds the safe bounds of the buffer
    if (ifd_offset < 8 || ifd_offset > state->data_len - 18) {
        return;
    }

    uint8_t *ifd_ptr = state->dptr + ifd_offset;
    uint16_t num_entries = iw_get_ui16_e(ifd_ptr, state->byte_order);

    if (num_entries > 1000) {
        return;
    }

    for (uint32_t i = 0; i < num_entries; i++) {
        uint32_t entry_offset = ifd_offset + 2 + i * 12;
        
        // Bounds check for the 12-byte EXIF entry
        if (entry_offset + 12 > state->data_len) {
            return;
        }

        uint8_t *entry_ptr = state->dptr + entry_offset;
        uint16_t tag_id = iw_get_ui16_e(entry_ptr, state->byte_order);

        int int_val;
        double dbl_val;

        switch (tag_id) {
            case 0x0100: // 256 - ImageWidth
                if (get_exif_tag_int_value(state, entry_offset, &int_val)) {
                    res->field_0x0 = int_val;
                }
                break;
            case 0x0112: // 274 - Orientation
                if (get_exif_tag_int_value(state, entry_offset, &int_val)) {
                    res->field_0x18 = int_val;
                }
                break;
            case 0x011a: // 282 - XResolution
                if (get_exif_tag_dbl_value(state, entry_offset, &dbl_val)) {
                    res->field_0x8 = dbl_val;
                }
                break;
            case 0x011b: // 283 - YResolution
                if (get_exif_tag_dbl_value(state, entry_offset, &dbl_val)) {
                    res->field_0x10 = dbl_val;
                }
                break;
            default:
                break;
        }
    }
}