int jpeg_size(const uint8_t *data, unsigned int size, int *width, int *height) {
    unsigned int pos = 0;

    // Check for SOI (Start of Image) marker: FF D8
    if (pos + 3 >= size) return -1;
    if (data[pos] != 0xFF || data[pos + 1] != 0xD8) return -1;

    // Check for APP0 marker: FF E0
    if (data[pos + 2] != 0xFF || data[pos + 3] != 0xE0) return -1;

    pos += 4;

    // Check for JFIF identifier string "JFIF\0"
    if (pos + 6 >= size) return -1;
    if (data[pos + 2] != 'J' || data[pos + 3] != 'F' || 
        data[pos + 4] != 'I' || data[pos + 5] != 'F' || data[pos + 6] != 0x00) {
        return -1;
    }

    // Read length of APP0 segment (big-endian)
    uint16_t len = (data[pos] << 8) | data[pos + 1];

    // Skip over the APP0 segment
    pos += len;

    // Iterate through JPEG markers to find the SOF (Start of Frame) marker
    while (pos < size) {
        pos += len;

        // Check bounds for the next marker
        if (pos + 1 >= size) return -1;

        // Every marker must start with 0xFF
        if (data[pos] != 0xFF) return -1;

        // Check if the marker is SOF0 (0xC0)
        if (data[pos + 1] == 0xC0) {
            // Extract height (big-endian)
            *height = (data[pos + 5] << 8) | data[pos + 6];
            // Extract width (big-endian)
            *width = (data[pos + 7] << 8) | data[pos + 8];
            
            return 0;
        } else {
            // For other markers, skip the segment based on its length
            pos += 2;
            len = (data[pos] << 8) | data[pos + 1];
        }
    }

    return -1;
}