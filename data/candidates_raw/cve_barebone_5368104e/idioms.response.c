int stream_read_ntlm_message(struct wstream *s, struct NTLM_MESSAGE_FIELDS *fields)
{
  if (fields->Len == 0)
    return 1;
  if (stream_get_left(s) < (fields->Len + fields->BufferOffset))
    return -1;
  if ((fields->Buffer = stream_get_buffer(fields->Len)) == ((void *)0))
    return -1;
  stream_skip(s, fields->BufferOffset);
  stream_read(s, fields->Buffer, fields->Len);
  return 1;
}