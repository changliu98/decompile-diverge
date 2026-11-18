bool __cdecl pmic_thermal_is_aux(int address)
{
  char v2; // [rsp+0h] [rbp-6h]
  char v3; // [rsp+1h] [rbp-5h]

  if ( address < 4 || address > 64 || (v3 = 1, (address - 4) % 12) )
  {
    v2 = 0;
    if ( address >= 8 )
    {
      v2 = 0;
      if ( address <= 68 )
        v2 = ~((address - 8) % 12 != 0);
    }
    v3 = v2;
  }
  return v3 & 1;
}