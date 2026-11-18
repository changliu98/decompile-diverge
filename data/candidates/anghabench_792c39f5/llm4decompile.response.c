int check_need_swap(int file_endian)
{
 int host_endian;
 u8 *check;
 int data;
 int file_endian_local;

 file_endian_local = file_endian;

 data = 0x12345678;
 check = (u8 *) &data;
 if (*check == 0x78) {
  host_endian = ELFDATA2LSB;
 } else {
  host_endian = ELFDATA2MSB;
 }

 if (host_endian == file_endian_local) {
  return 0;
 } else {
  return 1;
 }
}