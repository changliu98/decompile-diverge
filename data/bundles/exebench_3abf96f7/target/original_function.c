void MassRelease(double *InterceptedSnow, double *TempInterceptionStorage,
                 double *ReleasedMass, double *Drip )
{
  double TempDrip;
  double TempReleasedMass;
  double Threshold;
  double MaxRelease;




  if (*InterceptedSnow > 0.005) {
    Threshold = 0.10 * *InterceptedSnow;
    MaxRelease = 0.17 * *InterceptedSnow;







    if ((*TempInterceptionStorage) >= Threshold) {


      *Drip += Threshold;
      *InterceptedSnow -= Threshold;
      *TempInterceptionStorage -= Threshold;
      if (*InterceptedSnow < 0.005)
        TempReleasedMass = 0.0;
      else
        TempReleasedMass = ((*InterceptedSnow - 0.005) < MaxRelease) ? (*InterceptedSnow - 0.005) : MaxRelease
                                          ;
      *ReleasedMass += TempReleasedMass;
      *InterceptedSnow -= TempReleasedMass;
      MassRelease(InterceptedSnow, TempInterceptionStorage, ReleasedMass,
                  Drip);
    }

    else {
      TempDrip = (*TempInterceptionStorage < *InterceptedSnow) ? *TempInterceptionStorage : *InterceptedSnow;
      *Drip += TempDrip;
      *InterceptedSnow -= TempDrip;
    }
  }





  else {
    TempDrip = (*TempInterceptionStorage < *InterceptedSnow) ? *TempInterceptionStorage : *InterceptedSnow;
    *Drip += TempDrip;
    *InterceptedSnow -= TempDrip;
    *TempInterceptionStorage = 0.0;
  }
}