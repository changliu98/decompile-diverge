int __cdecl FS460_get_available_vga_modes(unsigned __int64 *p_vga_modes)
{
    if (p_vga_modes == NULL)
        return 4096; // Likely an "invalid parameter" error code (0x1000)

    *p_vga_modes = 31; // 0x1F, likely a bitmask representing available modes
    return 0;          // Success
}