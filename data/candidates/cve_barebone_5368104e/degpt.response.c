int ntlm_read_message_fields_buffer(wStream *stream, NTLM_MESSAGE_FIELDS *ntlm_fields)
{
    // Check if there is data to read in the buffer
    if (ntlm_fields->Len != 0) {
        // Verify that the stream has enough data remaining to read the buffer
        if (Stream_GetLength(stream) < ntlm_fields->BufferOffset + ntlm_fields->Len) {
            return -1;
        }
        // Allocate memory for the buffer
        ntlm_fields->Buffer = malloc(ntlm_fields->Len);
        if (ntlm_fields->Buffer == NULL) {
            return -1;
        }
        // Set the stream position to the buffer offset
        Stream_Seek(stream, ntlm_fields->BufferOffset);
        // Read the buffer data from the stream
        Stream_ReadBytes(stream, ntlm_fields->Buffer, ntlm_fields->Len);
    }
    return 1;
}