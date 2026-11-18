int __cdecl ntlm_read_message_fields_buffer(wStream *s, NTLM_MESSAGE_FIELDS *fields)
{
  size_t v3; // [rsp+0h] [rbp-20h]

  if ( !fields->Len )
    return 1;
  v3 = fields->Len + fields->BufferOffset;
  if ( v3 <= Stream_Length(s) )
  {
    fields->Buffer = (PBYTE)malloc(fields->Len);
    if ( !fields->Buffer )
      return -1;
    Stream_SetPosition(s, fields->BufferOffset);
    Stream_Read(s, fields->Buffer, fields->Len);
    return 1;
  }
  return -1;
}