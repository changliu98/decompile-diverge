static BOOL rdp_write_logon_info_v2(wStream* s, RDPCLIENT* This) {
  int domain_len;
  int password_len;
  if (Stream_EnsureRemainingCapacity(s, 576) == 0) return 0;
  Stream_Write_UINT16(s, 1);
  Stream_Write_UINT32(s, 18);
  Stream_Write_UINT32(s, This->logon_domain_len);
  domain_len = strnlen(This->logon_domain, 256);
  if (domain_len >= 0x7fffffff) return 0;
  Stream_Write_UINT32(s, (domain_len + 1) * 2);
  password_len = strnlen(This->logon_password, 256);
  if (password_len >= 0x7fffffff) return 0;
  Stream_Write_UINT32(s, (password_len + 1) * 2);
  Stream_Seek(s, 558);
  if (Stream_Write_UTF16_String_From_UTF8(s, domain_len + 1, This->logon_domain,
                                          domain_len, 1) < 0)
    return 0;
  if (Stream_Write_UTF16_String_From_UTF8(s, password_len + 1,
                                          This->logon_password, password_len,
                                          1) < 0)
    return 0;
  return 1;
}