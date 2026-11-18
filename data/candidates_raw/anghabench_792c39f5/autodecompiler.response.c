static int
elf_swap_endian(int file_endian)
{
 int host_endian;
 int test = 1;
 unsigned char *c = (unsigned char *) &test;

 if (*c == 1)
  host_endian = ELFDATA2LSB;
 else
  host_endian = ELFDATA2MSB;

 return (host_endian != file_endian) ? 1 : 0;
}