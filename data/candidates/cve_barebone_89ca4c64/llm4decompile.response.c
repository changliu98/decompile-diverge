BOOL
rdp_write_logon_info_v2(wStream *s, logon_info *info)
{
    UINT32 domainLen;
    UINT32 usernameLen;

    if (!Stream_EnsureRemainingCapacity(s, 576))
        return 0;

    Stream_Write_UINT16(s, 0x0001);
    Stream_Write_UINT32(s, 0x0012);
    Stream_Write_UINT32(s, info->sessionId);

    domainLen = strnlen(info->domain, 256);
    if (domainLen >= 0x7FFFFFFF)
        return 0;
    Stream_Write_UINT32(s, (domainLen + 1) * 2);

    usernameLen = strnlen(info->username, 256);
    if (usernameLen >= 0x7FFFFFFF)
        return 0;
    Stream_Write_UINT32(s, (usernameLen + 1) * 2);

    Stream_Seek(s, 558);

    if (Stream_Write_UTF16_String_From_UTF8(s, domainLen + 1, info->domain, domainLen, 1) < 0)
        return 0;
    if (Stream_Write_UTF16_String_From_UTF8(s, usernameLen + 1, info->username, usernameLen, 1) < 0)
        return 0;

    return 1;
}