void __cdecl MassRelease(double *InterceptedSnow, double *TempInterceptionStorage, double *ReleasedMass, double *Drip)
{
    double threshold;
    double maxRelease;
    double tempReleasedMass;
    double dripAmount;

    // If the intercepted snow is negligible, drain the temporary storage and return
    if (*InterceptedSnow <= 0.005)
    {
        dripAmount = fmin(*InterceptedSnow, *TempInterceptionStorage);
        *Drip += dripAmount;
        *InterceptedSnow -= dripAmount;
        *TempInterceptionStorage = 0.0;
        return;
    }

    threshold = 0.1 * *InterceptedSnow;
    maxRelease = 0.17 * *InterceptedSnow;

    // If temporary storage is below the threshold, drain up to the available storage
    if (*TempInterceptionStorage < threshold)
    {
        dripAmount = fmin(*InterceptedSnow, *TempInterceptionStorage);
        *Drip += dripAmount;
        *InterceptedSnow -= dripAmount;
        return;
    }

    // Otherwise, apply the threshold drip and calculate mass release
    *Drip += threshold;
    *InterceptedSnow -= threshold;
    *TempInterceptionStorage -= threshold;

    if (*InterceptedSnow >= 0.005)
    {
        // Release mass, ensuring we leave at least 0.005 in intercepted snow
        tempReleasedMass = fmin(maxRelease, *InterceptedSnow - 0.005);
    }
    else
    {
        tempReleasedMass = 0.0;
    }

    *ReleasedMass += tempReleasedMass;
    *InterceptedSnow -= tempReleasedMass;

    // Recursively call to process further releases
    MassRelease(InterceptedSnow, TempInterceptionStorage, ReleasedMass, Drip);
}