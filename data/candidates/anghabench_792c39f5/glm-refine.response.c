bool __cdecl check_need_swap(int file_endian)
{
    // Returns true if the file's endianness does not match the host system's little-endian format
    return file_endian != ELFDATA2LSB;
}