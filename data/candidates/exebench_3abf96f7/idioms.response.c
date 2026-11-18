void SnowInterception(double *InterceptedSnow, double *TempInterceptionStorage, double *ReleasedMass, double *Drip)
{
  double Threshold;
  double MaxRelease;
  double TempReleasedMass;
  if (*InterceptedSnow > 0.005)
  {
    Threshold = *InterceptedSnow * 0.10;
    MaxRelease = *InterceptedSnow * 0.17;
    if (*TempInterceptionStorage >= Threshold)
    {
      *Drip += Threshold;
      *InterceptedSnow -= Threshold;
      *TempInterceptionStorage -= Threshold;
      if (*InterceptedSnow < 0.005)
      {
        TempReleasedMass = 0.0;
      }
      else
      {
        if (*InterceptedSnow - 0.005 < MaxRelease)
        {
          TempReleasedMass = *InterceptedSnow - 0.005;
        }
        else
        {
          TempReleasedMass = MaxRelease;
        }
      }
      *ReleasedMass += TempReleasedMass;
      *InterceptedSnow -= TempReleasedMass;
      MassRelease(InterceptedSnow,TempInterceptionStorage,ReleasedMass,Drip);
    }
    else
    {
      if (*InterceptedSnow > *TempInterceptionStorage)
      {
        *Drip += *TempInterceptionStorage;
        *InterceptedSnow -= *TempInterceptionStorage;
      }
      else
      {
        *Drip += *InterceptedSnow;
        *InterceptedSnow -= *InterceptedSnow;
      }
    }
  }
  else
  {
    if (*InterceptedSnow > *TempInterceptionStorage)
    {
      *Drip += *TempInterceptionStorage;
      *InterceptedSnow -= *TempInterceptionStorage;
    }
    else
    {
      *Drip += *InterceptedSnow;
      *InterceptedSnow -= *InterceptedSnow;
    }
    *TempInterceptionStorage = 0.0;
  }
}