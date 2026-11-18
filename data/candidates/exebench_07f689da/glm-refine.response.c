void __cdecl Mat_GetLibraryVersion(int *major, int *minor, int *release)
{
  if (!major || !minor || !release)
    return;

  *major   = 1;
  *minor   = 5;
  *release = 9;
}