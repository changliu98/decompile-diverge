static int ntlm_read_message_fields_buffer(Stream *s, ntlm_message *msg) {
  if (msg->fields_buffer_length == 0) return 1;
  if (msg->fields_buffer_offset + msg->fields_buffer_length > Stream_Length(s))
    return -1;
  msg->fields_buffer = malloc(msg->fields_buffer_length);
  if (msg->fields_buffer == NULL) return -1;
  Stream_SetPosition(s, msg->fields_buffer_offset);
  Stream_Read(s, msg->fields_buffer, msg->fields_buffer_length);
  return 1;
}