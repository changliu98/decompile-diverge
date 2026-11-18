int read_new_config_info(WavpackContext *wpc, WavpackMetadata *wpmd)
{
    // Extract byte length and data pointer from the metadata block
    int metadata_size = wpmd->byte_length;
    uchar *metadata_buffer = wpmd->data;

    // Initialize version five flag and reset channel layout, qmode, and file format
    wpc->version_five = 1;
    wpc->channel_layout = 0;
    wpc->config.qmode = 0;
    wpc->file_format = '\0';

    // Free any existing channel reordering array to prevent memory leaks
    if (wpc->channel_reordering != NULL) {
        free(wpc->channel_reordering);
        wpc->channel_reordering = NULL;
    }

    // Process the metadata if there is data present
    if (metadata_size != 0) {
        // Parse file format from the first byte
        wpc->file_format = *metadata_buffer;
        // Update qmode with the second byte, preserving upper bits
        wpc->config.qmode = (wpc->config.qmode & 0xffffff00U) | (uint)metadata_buffer[1];

        // If there are more than 2 bytes, parse channel layout information
        if (metadata_size != 2) {
            // Start building channel layout from the third byte
            wpc->channel_layout = (uint)metadata_buffer[2] << 0x10;

            // Handle different lengths of channel layout data
            if (metadata_size == 3) {
                // For 3-byte length, add number of channels directly
                wpc->channel_layout += wpc->config.num_channels;
            } else {
                // For longer lengths, read number of channels from the fourth byte
                uint channel_count = (uint)metadata_buffer[3];
                wpc->channel_layout += channel_count;

                // Calculate remaining bytes after parsing channel count
                int bytes_left = metadata_size - 4;
                if (bytes_left != 0) {
                    // Validate that there are enough bytes for channel reordering
                    if ((int)channel_count > bytes_left) {
                        return 0;
                    }

                    // Allocate memory for channel reordering array
                    wpc->channel_reordering = malloc(channel_count);
                    if (wpc->channel_reordering != NULL) {
                        // Populate channel reordering array from remaining data
                        for (uint channel_index = 0; channel_index < channel_count; channel_index++) {
                            if (bytes_left == 0) {
                                // Default to identity mapping if no more data
                                wpc->channel_reordering[channel_index] = (uchar)channel_index;
                            } else {
                                // Read channel reordering value from data
                                wpc->channel_reordering[channel_index] = *metadata_buffer;
                                bytes_left--;
                                metadata_buffer++;
                            }
                        }
                    }
                }
            }
        }
    }
    // Return success
    return 1;
}