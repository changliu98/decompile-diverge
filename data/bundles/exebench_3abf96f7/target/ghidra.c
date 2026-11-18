void MassRelease(double *InterceptedSnow,double *TempInterceptionStorage,double *ReleasedMass,
                double *Drip)

{
  double dVar1;
  double local_60;
  double local_58;
  double local_50;
  double MaxRelease;
  double Threshold;
  double TempReleasedMass;
  double TempDrip;
  double *Drip_local;
  double *ReleasedMass_local;
  double *TempInterceptionStorage_local;
  double *InterceptedSnow_local;
  
  if (*InterceptedSnow <= DAT_00102008) {
    if (*InterceptedSnow <= *TempInterceptionStorage) {
      local_60 = *InterceptedSnow;
    }
    else {
      local_60 = *TempInterceptionStorage;
    }
    *Drip = local_60 + *Drip;
    *InterceptedSnow = *InterceptedSnow - local_60;
    *TempInterceptionStorage = 0.0;
  }
  else {
    dVar1 = DAT_00102018 * *InterceptedSnow;
    local_50 = DAT_00102010 * *InterceptedSnow;
    if (*TempInterceptionStorage < dVar1) {
      if (*InterceptedSnow <= *TempInterceptionStorage) {
        local_58 = *InterceptedSnow;
      }
      else {
        local_58 = *TempInterceptionStorage;
      }
      *Drip = local_58 + *Drip;
      *InterceptedSnow = *InterceptedSnow - local_58;
    }
    else {
      *Drip = dVar1 + *Drip;
      *InterceptedSnow = *InterceptedSnow - dVar1;
      *TempInterceptionStorage = *TempInterceptionStorage - dVar1;
      if (DAT_00102008 < *InterceptedSnow || DAT_00102008 == *InterceptedSnow) {
        if (*InterceptedSnow - DAT_00102008 < local_50) {
          local_50 = *InterceptedSnow - DAT_00102008;
        }
        TempReleasedMass = local_50;
      }
      else {
        TempReleasedMass = 0.0;
      }
      *ReleasedMass = TempReleasedMass + *ReleasedMass;
      *InterceptedSnow = *InterceptedSnow - TempReleasedMass;
      MassRelease(InterceptedSnow,TempInterceptionStorage,ReleasedMass,Drip);
    }
  }
  return;
}