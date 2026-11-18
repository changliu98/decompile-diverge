Assuming standard Windows types like PBYTE are used

int __cdecl ntlm_read_message_fields_buffer(wStream *s, NTLM_MESSAGE_FIELDS *fields)
{
    size_t end_offset;

    // If the length of the field is 0, there is no buffer to read
    if (!fields->Len)
        return 1;

    // Calculate the absolute end offset of the buffer within the stream
    end_offset = fields->Len + fields->BufferOffset;

    // Check for buffer overflow / out-of-bounds read
    if (end_offset <= Stream_Length(s))
    {
        // Allocate memory for the target buffer
        fields->Buffer = (PBYTE)malloc(fields->Len);
        if (!fields->Buffer)
            return -1; // Allocation failed

        // Seek to the offset and read the data into the newly allocated buffer
        Stream_SetPosition(s, fields->BufferOffset);
        Stream_Read(s, fields->Buffer, fields->Len);
        
        return 1; // Success
    }

    return -1; // Out of bounds
}