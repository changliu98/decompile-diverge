void sha1_update(SHA1_CTX *context, BYTE *input_buffer, size_t buffer_size)
{
    // Iterate through each byte of the input data
    for (size_t index = 0; index < buffer_size; index++) {
        // Store the current byte in the context's data buffer
        context->data[context->datalen] = input_buffer[index];
        // Increment the count of bytes stored in the buffer
        context->datalen++;
        // If the buffer is full (64 bytes), process it
        if (context->datalen == 0x40) {
            // Perform the SHA-1 transformation on the full block
            sha1_transform(context, context->data);
            // Add 512 bits (0x200) to the total bit length processed
            context->bitlen += 0x200;
            // Reset the data buffer length counter
            context->datalen = 0;
        }
    }
}