int ntlm_read_message_fields_buffer(wStream *s,NTLM_MESSAGE_FIELDS *fields)

{
  ushort uVar1;
  UINT32 UVar2;
  size_t sVar3;
  PBYTE pBVar4;
  NTLM_MESSAGE_FIELDS *fields_local;
  wStream *s_local;
  
  if (fields->Len != 0) {
    UVar2 = fields->BufferOffset;
    uVar1 = fields->Len;
    sVar3 = Stream_Length(s);
    if (sVar3 < UVar2 + uVar1) {
      return -1;
    }
    pBVar4 = malloc((ulong)fields->Len);
    fields->Buffer = pBVar4;
    if (fields->Buffer == (PBYTE)0x0) {
      return -1;
    }
    Stream_SetPosition(s,(ulong)fields->BufferOffset);
    Stream_Read(s,fields->Buffer,(ulong)fields->Len);
  }
  return 1;
}