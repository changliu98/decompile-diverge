int ntlm_read_message_fields_buffer(Stream* stream, MessageFieldsBuffer* fields) {
    int status = -1; // Default error status

    if (fields->Length > 0) {
        uint32_t end_pos = fields->Offset + fields->Length;
        
        if (end_pos > Stream_Length(stream)) {
            return -1;
        }

        fields->Buffer = malloc(fields->Length);
        
        if (fields->Buffer == NULL) {
            return -1;
        }

        Stream_SetPosition(stream, fields->Offset);
        Stream_Read(stream, fields->Buffer, fields->Length);
    }

    status = 1;
    return status;
}