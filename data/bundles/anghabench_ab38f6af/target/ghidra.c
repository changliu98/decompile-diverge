uint ad7192_get_temp_scale(bool unipolar)

{
  uint uVar1;
  bool unipolar_local;
  
  uVar1 = 0xaff;
  if (unipolar != 0) {
    uVar1 = 0x15fe;
  }
  return uVar1;
}