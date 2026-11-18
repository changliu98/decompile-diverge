void MassRelease(double *InterceptedSnow,
                 double *TempInterceptionStorage,
                 double *ReleasedMass,
                 double *Drip)
# 126 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/YifanCheng/VIC/refs/heads/master/external/VIC/src/lakes.eb.c"
{

  double MaxDrip, MaxRelease, Release, DripAdd, DripPerc;

  if (*InterceptedSnow > 0.005) {

    MaxDrip = 0.1 * *InterceptedSnow;
    MaxRelease = 0.17 * *InterceptedSnow;

    if (*TempInterceptionStorage >= MaxDrip) {

      DripAdd = MaxDrip + *Drip;
      *InterceptedSnow -= MaxDrip;
      *TempInterceptionStorage -= MaxDrip;

      if (*InterceptedSnow < 0.005) {
        Release = -(*InterceptedSnow);
      }
      else {
        if ((*InterceptedSnow - 0.005) < MaxRelease) {
          Release = *InterceptedSnow - 0.005;
        }
        else {
          Release = MaxRelease;
        }
      }

      *ReleasedMass += Release;
      *InterceptedSnow -= Release;

      MassRelease(InterceptedSnow, TempInterceptionStorage, ReleasedMass, Drip);

    }

    else {

      if (*TempInterceptionStorage < *InterceptedSnow) {
        DripPerc = *TempInterceptionStorage;
      }
      else {
        DripPerc = *InterceptedSnow;
      }

      DripAdd = DripPerc + *Drip;
      *InterceptedSnow -= DripPerc;

    }

    *Drip = DripAdd;

  }

  else {

    if (*TempInterceptionStorage < *InterceptedSnow) {
      DripPerc = *TempInterceptionStorage;
    }
    else {
      DripPerc = *InterceptedSnow;
    }

    DripAdd = DripPerc + *Drip;
    *InterceptedSnow -= DripPerc;

    *TempInterceptionStorage = 0.0;

  }

}