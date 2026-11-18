void MassRelease(double *InterceptedSnow, double *TempInterceptionStorage,
                 double *ReleasedMass, double *Drip)
# 298 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/YifanCheng/VIC/refs/heads/master/external/VIC/src/lakes.eb.c"
{
  double MaxRelease;
  double Threshold;
  double TempDrip;
  double TempReleasedMass;


  if (*InterceptedSnow > 0.0) {

    Threshold = 0.05 * (*InterceptedSnow);
    MaxRelease = 0.2 * (*InterceptedSnow);


    if (*TempInterceptionStorage >= Threshold) {

      *Drip += Threshold;
      *InterceptedSnow -= Threshold;
      *TempInterceptionStorage -= Threshold;


      if (*InterceptedSnow > 0.0) {
        TempReleasedMass = MaxRelease;
        if (TempReleasedMass > (*InterceptedSnow - 0.05))
          TempReleasedMass = *InterceptedSnow - 0.05;
      }
      else
        TempReleasedMass = 0.0;

      *ReleasedMass += TempReleasedMass;
      *InterceptedSnow -= TempReleasedMass;


      MassRelease(InterceptedSnow, TempInterceptionStorage, ReleasedMass, Drip);
    }


    else {
      TempDrip = *TempInterceptionStorage;
      if (TempDrip > *InterceptedSnow)
        TempDrip = *InterceptedSnow;
      *Drip += TempDrip;
      *InterceptedSnow -= TempDrip;
    }
  }


  else {
    TempDrip = *TempInterceptionStorage;
    if (TempDrip > *InterceptedSnow)
      TempDrip = *InterceptedSnow;
    *Drip += TempDrip;
    *InterceptedSnow -= TempDrip;
    *TempInterceptionStorage = 0.0;
  }

}