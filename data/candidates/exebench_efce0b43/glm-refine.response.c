void __cdecl rbc_force_stat(float *pArea, float *pVolume)
{
  if (pArea) {
    *pArea = 1.0f;   // Force area to unit area
  }

  if (pVolume) {
    *pVolume = 1.0f; // Force volume to unit volume
  }
}