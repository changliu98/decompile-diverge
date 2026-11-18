void __cdecl Mat_GetLibraryVersion(int *major, int *minor, int *release)
{
  if ( major )
    *major = 1;
  if ( minor )
    *minor = 5;
  if ( release )
    *release = 9;
}