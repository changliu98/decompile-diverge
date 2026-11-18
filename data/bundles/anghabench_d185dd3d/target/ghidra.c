bool pmic_thermal_is_aux(int address)

{
  undefined1 local_e;
  undefined1 local_d;
  int address_local;
  
  if (((address < 4) || (0x40 < address)) || (local_d = 1, (address + -4) % 0xc != 0)) {
    local_e = 0;
    if ((7 < address) && (local_e = 0, address < 0x45)) {
      local_e = (address + -8) % 0xc != 0 ^ 0xff;
    }
    local_d = local_e;
  }
  return (bool)(local_d & 1);
}