void Mat_GetLibraryVersion(int *major,int *minor,int *release)

{
  int *release_local;
  int *minor_local;
  int *major_local;
  
  if (major != (int *)0x0) {
    *major = 1;
  }
  if (minor != (int *)0x0) {
    *minor = 5;
  }
  if (release != (int *)0x0) {
    *release = 9;
  }
  return;
}