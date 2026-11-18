int read_new_config_info(WavpackContext *context, WavpackMetadata *metadata_block)
{
    // Extract the byte length and data pointer from the metadata block
    int metadata_length = metadata_block->byte_length;
    uchar *metadata_buffer = metadata_block->data;

    // Initialize version five flag and reset channel layout, qmode, and file format
    context->version_five = 1;
    context->channel_layout = 0;
    context->config.qmode = 0;
    context->file_format = '\0';

    // Free any previously allocated channel reordering array to prevent memory leaks
    if (context->channel_reordering != NULL) {
        free(context->channel_reordering);
        context->channel_reordering = NULL;
    }

    // Process the metadata only if there is data present
    if (metadata_length != 0) {
        // Parse the file format from the first byte
        context->file_format = *metadata_buffer;
        // Update the lower 8 bits of qmode with the second byte
        context->config.qmode = (context->config.qmode & 0xffffff00U) | (uint)metadata_buffer[1];

        // If there are more than 2 bytes, parse channel layout information
        if (metadata_length != 2) {
            // Start building the channel layout from the third byte (shifted to upper bits)
            context->channel_layout = (uint)metadata_buffer[2] << 0x10;

            // Handle different lengths of channel layout data
            if (metadata_length == 3) {
                // For 3-byte length, add the number of channels to the layout
                context->channel_layout += context->config.num_channels;
            } else {
                // For longer lengths, read the number of reorder bytes from the fourth byte
                uint reorder_array_size = (uint)metadata_buffer[3];
                // Add the number of reorder bytes to the channel layout
                context->channel_layout += reorder_array_size;

                // Calculate remaining bytes after the first 4 bytes
                int buffer_remaining = metadata_length - 4;
                if (buffer_remaining != 0) {
                    // Validate that there are enough bytes for the reorder data
                    if ((int)reorder_array_size > buffer_remaining) {
                        return 0;
                    }

                    // Allocate memory for the channel reordering array
                    context->channel_reordering = malloc(reorder_array_size);
                    if (context->channel_reordering != NULL) {
                        // Populate the reordering array with data from the metadata
                        for (int index = 0; index < reorder_array_size; index++) {
                            if (buffer_remaining == 0) {
                                // If no more data bytes, use index as default value
                                context->channel_reordering[index] = (uchar)index;
                            } else {
                                // Otherwise, read the next byte from the data stream
                                context->channel_reordering[index] = *metadata_buffer;
                                metadata_buffer++;
                                buffer_remaining--;
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