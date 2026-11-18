BOOL rdp_write_logon_info_v2(Stream* stream, rdp_logon_info_v2* info) {
    size_t len1 = 0;
    size_t len2 = 0;

    if (!Stream_EnsureRemainingCapacity(stream, 0x240)) {
        return FALSE;
    }

    Stream_Write_UINT16(stream, 1);
    Stream_Write_UINT32(stream, 0x12);
    Stream_Write_UINT32(stream, info->field_0);

    len1 = strnlen(info->field_10, 0x100);
    if (len1 >= 0x7fffffff) {
        return FALSE;
    }
    Stream_Write_UINT32(stream, (uint32_t)((len1 + 1) * 2));

    len2 = strnlen(info->field_8, 0x100);
    if (len2 >= 0x7fffffff) {
        return FALSE;
    }
    Stream_Write_UINT32(stream, (uint32_t)((len2 + 1) * 2));

    Stream_Seek(stream, 0x22e);

    if (Stream_Write_UTF16_String_From_UTF8(stream, len1 + 1, info->field_10, len1, 1) < 0) {
        return FALSE;
    }

    if (Stream_Write_UTF16_String_From_UTF8(stream, len2 + 1, info->field_8, len2, 1) < 0) {
        return FALSE;
    }

    return TRUE;
}