void md5_update(MD5_CTX *context, BYTE *input_data, size_t data_length)
{
    // Iterate through each byte of the input data
    for (size_t index = 0; index < data_length; index++) {
        // Store the current byte in the context's data buffer
        context->data[context->datalen] = input_data[index];
        // Increment the count of bytes stored in the buffer
        context->datalen++;
        // If the buffer is full (64 bytes), process it
        if (context->datalen == 0x40) {
            // Perform the MD5 transformation on the full block
            md5_transform(context, context->data);
            // Add 512 bits (64 bytes) to the total bit length processed
            context->bitlen += 0x200;
            // Reset the data buffer length counter
            context->datalen = 0;
        }
    }
}