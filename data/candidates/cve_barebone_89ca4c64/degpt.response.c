BOOL rdp_write_logon_info_v2(wStream *s,logon_info *info)

{
  BOOL BVar1;
  size_t length;
  size_t length_00;
  SSIZE_T SVar2;
  size_t usernameLen;
  size_t domainLen;
  logon_info *info_local;
  wStream *s_local;
  BOOL local_c;
  
  BVar1 = Stream_EnsureRemainingCapacity(s,0x240);
  if (BVar1 == 0) {
    local_c = 0;
  }
  else {
    Stream_Write_UINT16(s,1);
    Stream_Write_UINT32(s,0x12);
    Stream_Write_UINT32(s,info->sessionId);
    length = strnlen(info->domain,0x100);
    if (length < 0x7fffffff) {
      Stream_Write_UINT32(s,((int)length + 1) * 2);
      length_00 = strnlen(info->username,0x100);
      if (length_00 < 0x7fffffff) {
        Stream_Write_UINT32(s,((int)length_00 + 1) * 2);
        Stream_Seek(s,0x22e);
        SVar2 = Stream_Write_UTF16_String_From_UTF8(s,length + 1,info->domain,length,1);
        if (SVar2 < 0) {
          local_c = 0;
        }
        else {
          SVar2 = Stream_Write_UTF16_String_From_UTF8(s,length_00 + 1,info->username,length_00,1);
          if (SVar2 < 0) {
            local_c = 0;
          }
          else {
            local_c = 1;
          }
        }
      }
      else {
        local_c = 0;
      }
    }
    else {
      local_c = 0;
    }
  }
  return local_c;
}