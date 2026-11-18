int obdRevConvert_04(float fuel, unsigned int *pFuel, unsigned int *pFuelRate,
                     unsigned int *pFuelRateInstant,
                     unsigned int *pFuelRateAverage) {
  *pFuel = (unsigned int)((fuel * 255) / 100);
  return 1;
}