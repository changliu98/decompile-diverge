bool __cdecl check_need_swap(int file_endian)
{
  return ELFDATA2LSB != file_endian;
}