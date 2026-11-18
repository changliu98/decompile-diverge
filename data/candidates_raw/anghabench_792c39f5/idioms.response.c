static int is_elf_little_endian(int file_endian)
{
  return (file_endian != ELFDATA2LSB);
}