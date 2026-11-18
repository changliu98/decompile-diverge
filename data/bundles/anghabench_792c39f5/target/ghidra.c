/* WARNING: Removing unreachable block (ram,0x001011f1) */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

bool check_need_swap(int file_endian)

{
  int host_endian;
  u8 *check;
  int data;
  int file_endian_local;
  
  return (bool)(ELFDATA2LSB != file_endian);
}