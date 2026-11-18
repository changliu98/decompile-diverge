BOOL __cdecl rdp_write_logon_info_v2(wStream *s, logon_info *info)
{
    size_t domainLen;
    size_t usernameLen;
    BOOL status;

    // RDP Logon Info V2 requires a fixed total size of 576 bytes (0x240)
    if (!Stream_EnsureRemainingCapacity(s, 0x240))
        return FALSE;

    // Field 1: cbDomain (fixed to 1 for V2)
    Stream_Write_UINT16(s, 1);
    
    // Field 2: Flags (0x12 indicates Logon Info V2)
    Stream_Write_UINT32(s, 0x12);
    
    // Field 3: Session ID
    Stream_Write_UINT32(s, info->sessionId);

    // Calculate domain length (max 256 chars) and validate against INT32_MAX
    domainLen = strnlen(info->domain, 0x100);
    if (domainLen >= 0x7FFFFFFF)
        return FALSE;
    
    // Field 4: Domain size in bytes (UTF-16, including null terminator)
    Stream_Write_UINT32(s, 2 * (domainLen + 1));

    // Calculate username length (max 256 chars) and validate against INT32_MAX
    usernameLen = strnlen(info->username, 0x100);
    if (usernameLen >= 0x7FFFFFFF)
        return FALSE;
    
    // Field 5: Username size in bytes (UTF-16, including null terminator)
    Stream_Write_UINT32(s, 2 * (usernameLen + 1));

    // Field 6: Skip 558 bytes (0x22E). This pads the header and reserves space 
    // for the actual UTF-16 domain and username strings that are written later.
    Stream_Seek(s, 0x22E);

    // Convert and write the domain and username strings into the reserved space.
    // The function returns a negative value on failure.
    status = (Stream_Write_UTF16_String_From_UTF8(s, domainLen + 1, info->domain, domainLen, 1) >= 0)
          && (Stream_Write_UTF16_String_From_UTF8(s, usernameLen + 1, info->username, usernameLen, 1) >= 0);

    return status;
}