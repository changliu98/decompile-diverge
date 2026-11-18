int read_new_config_info(WavpackContext *context, WavpackMetadata *metadata)
{
    // Extract the byte length and data pointer from the metadata structure
    int data_size = metadata->byte_length;
    uchar *data_ptr = metadata->data;

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

    // Process the configuration data if byte_length is non-zero
    if (data_size != 0) {
        // Parse the file format from the first byte
        context->file_format = *data_ptr;
        // Update the lower 8 bits of qmode with the second byte
        context->config.qmode = (context->config.qmode & 0xffffff00U) | (uint)data_ptr[1];

        // If there are more than 2 bytes, parse channel layout information
        if (data_size != 2) {
            // Set the upper bits of channel_layout from the third byte
            context->channel_layout = (uint)data_ptr[2] << 0x10;

            // If exactly 3 bytes, add the configured number of channels to the layout
            if (data_size == 3) {
                context->channel_layout += context->config.num_channels;
            } else {
                // If more than 3 bytes, read the number of channels from the fourth byte
                uint channel_count = (uint)data_ptr[3];
                context->channel_layout += channel_count;

                // Calculate the remaining bytes after the first 4
                int bytes_left = data_size - 4;
                if (bytes_left != 0) {
                    // Validate that there are enough bytes for channel reordering data
                    if ((int)channel_count > bytes_left) {
                        return 0;
                    }

                    // Allocate memory for the channel reordering array
                    context->channel_reordering = malloc(channel_count);
                    if (context->channel_reordering != NULL) {
                        // Populate the reordering array with channel indices or data bytes
                        for (uint index = 0; index < channel_count; index++) {
                            if (bytes_left == 0) {
                                // If no more data bytes, use the channel index as the reordering value
                                context->channel_reordering[index] = (uchar)index;
                            } else {
                                // Otherwise, use the next data byte for reordering
                                context->channel_reordering[index] = *data_ptr;
                                bytes_left--;
                                data_ptr++;
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