int read_new_config_info(WavpackContext *context, WavpackMetadata *metadata)
{
    // Extract byte length and data pointer from the metadata structure
    int data_size = metadata->byte_length;
    uchar *buffer = metadata->data;

    // Initialize version five flag and reset channel layout, qmode, and file format
    context->version_five = 1;
    context->channel_layout = 0;
    context->config.qmode = 0;
    context->file_format = '\0';

    // Free any existing channel reordering array to prevent memory leaks
    if (context->channel_reordering != NULL) {
        free(context->channel_reordering);
        context->channel_reordering = NULL;
    }

    // Process configuration data only if byte length is non-zero
    if (data_size != 0) {
        // Set file format from the first byte of data
        context->file_format = *buffer;
        
        // Update qmode: preserve upper bits and set lower 8 bits from data[1]
        context->config.qmode = (context->config.qmode & 0xffffff00U) | (uint)buffer[1];

        // Process channel layout if byte length is greater than 2
        if (data_size != 2) {
            // Initialize channel layout with data[2] shifted to bits 16-23
            context->channel_layout = (uint)buffer[2] << 0x10;

            // Handle different byte lengths for channel layout and reordering
            if (data_size == 3) {
                // For 3-byte length, add number of channels to channel layout
                context->channel_layout += context->config.num_channels;
            } else {
                // For longer lengths, read number of channels from data[3]
                uint channel_count = (uint)buffer[3];
                context->channel_layout += channel_count;

                // Calculate remaining bytes after the first 4 bytes
                int bytes_left = data_size - 4;
                
                // Process channel reordering if there are remaining bytes
                if (bytes_left != 0) {
                    // Validate that there are enough bytes for the number of channels
                    if ((int)channel_count > bytes_left) {
                        return 0;
                    }

                    // Allocate memory for channel reordering array
                    context->channel_reordering = malloc((size_t)channel_count);
                    if (context->channel_reordering != NULL) {
                        // Populate channel reordering array
                        for (int index = 0; index < (int)channel_count; index++) {
                            // If no more data bytes, use default index; otherwise read from data
                            if (bytes_left == 0) {
                                context->channel_reordering[index] = (uchar)index;
                            } else {
                                context->channel_reordering[index] = *buffer;
                                bytes_left--;
                                buffer++;
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