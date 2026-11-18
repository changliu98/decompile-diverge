BOOL __cdecl rdp_write_logon_info_v2(wStream *s, logon_info *info)
{
  size_t usernameLen; // [rsp+8h] [rbp-28h]
  size_t domainLen; // [rsp+10h] [rbp-20h]

  if ( !Stream_EnsureRemainingCapacity(s, 0x240uLL) )
    return 0;
  Stream_Write_UINT16(s, 1u);
  Stream_Write_UINT32(s, 0x12u);
  Stream_Write_UINT32(s, info->sessionId);
  domainLen = strnlen(info->domain, 0x100uLL);
  if ( domainLen >= 0x7FFFFFFF )
    return 0;
  Stream_Write_UINT32(s, 2 * (domainLen + 1));
  usernameLen = strnlen(info->username, 0x100uLL);
  if ( usernameLen >= 0x7FFFFFFF )
    return 0;
  Stream_Write_UINT32(s, 2 * (usernameLen + 1));
  Stream_Seek(s, 0x22EuLL);
  return Stream_Write_UTF16_String_From_UTF8(s, domainLen + 1, info->domain, domainLen, 1) >= 0
      && Stream_Write_UTF16_String_From_UTF8(s, usernameLen + 1, info->username, usernameLen, 1) >= 0;
}