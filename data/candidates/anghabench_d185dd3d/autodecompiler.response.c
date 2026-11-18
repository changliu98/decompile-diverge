static int pmic_thermal_is_aux(int channel)
{
 unsigned char valid;

 if ((channel >= 5 && channel <= 64 && (channel - 4) % 12 == 0) ||
     (channel >= 9 && channel <= 68 && (channel - 8) % 12 == 0))
  valid = 1;
 else
  valid = 0;

 return valid & 1;
}