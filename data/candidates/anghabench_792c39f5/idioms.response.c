static int check_need_swap(int file_endian)
{
  return (file_endian != ELFDATA2LSB);
}