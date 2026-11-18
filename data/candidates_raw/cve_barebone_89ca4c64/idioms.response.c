int smb_logon(struct wstream *s, struct logon_info *info)
{
  long domainLen; long usernameLen;
  if (!smb_write_word(s, 0x240))
    return 0;
  smb_write_byte(s, 1);
  smb_write_word(s, 0x12);
  smb_write_word(s, info->sessionId);
  if ((domainLen = smb_write_string(info->domain, 256)) < 0)
    return 0;
  smb_write_word(s, (domainLen * 2 + 2));
  if ((usernameLen = smb_write_string(info->username, 256)) < 0)
    return 0;
  smb_write_word(s, (usernameLen * 2 + 2));
  smb_write_word(s, 0x22e);
  if (smb_write_string_with_length(s, domainLen + 1, info->domain, domainLen, 1) < 0)
    return 0;
  if (smb_write_string_with_length(s, usernameLen + 1, info->username, usernameLen, 1) < 0)
    return 0;
  return 1;
}