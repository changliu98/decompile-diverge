void __cdecl MassRelease(double *InterceptedSnow, double *TempInterceptionStorage, double *ReleasedMass, double *Drip)
{
  double v4; // [rsp+8h] [rbp-58h]
  double v5; // [rsp+10h] [rbp-50h]
  double v6; // [rsp+18h] [rbp-48h]
  double MaxRelease; // [rsp+20h] [rbp-40h]
  double Threshold; // [rsp+28h] [rbp-38h]
  double TempReleasedMass; // [rsp+30h] [rbp-30h]

  if ( *InterceptedSnow <= 0.005 )
  {
    if ( *InterceptedSnow <= *TempInterceptionStorage )
      v4 = *InterceptedSnow;
    else
      v4 = *TempInterceptionStorage;
    *Drip = v4 + *Drip;
    *InterceptedSnow = *InterceptedSnow - v4;
    *TempInterceptionStorage = 0.0;
  }
  else
  {
    Threshold = 0.1 * *InterceptedSnow;
    MaxRelease = 0.17 * *InterceptedSnow;
    if ( *TempInterceptionStorage < Threshold )
    {
      if ( *InterceptedSnow <= *TempInterceptionStorage )
        v5 = *InterceptedSnow;
      else
        v5 = *TempInterceptionStorage;
      *Drip = v5 + *Drip;
      *InterceptedSnow = *InterceptedSnow - v5;
    }
    else
    {
      *Drip = Threshold + *Drip;
      *InterceptedSnow = *InterceptedSnow - Threshold;
      *TempInterceptionStorage = *TempInterceptionStorage - Threshold;
      if ( *InterceptedSnow >= 0.005 )
      {
        if ( MaxRelease <= *InterceptedSnow - 0.005 )
          v6 = MaxRelease;
        else
          v6 = *InterceptedSnow - 0.005;
        TempReleasedMass = v6;
      }
      else
      {
        TempReleasedMass = 0.0;
      }
      *ReleasedMass = TempReleasedMass + *ReleasedMass;
      *InterceptedSnow = *InterceptedSnow - TempReleasedMass;
      MassRelease(InterceptedSnow, TempInterceptionStorage, ReleasedMass, Drip);
    }
  }
}