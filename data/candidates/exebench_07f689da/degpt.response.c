void Mat_GetLibraryVersion(int *version_major,int *version_minor,int *version_release)
{
  // Set the major version number if the pointer is not NULL
  if (version_major) *version_major = 1;
  // Set the minor version number if the pointer is not NULL
  if (version_minor) *version_minor = 5;
  // Set the release version number if the pointer is not NULL
  if (version_release) *version_release = 9;
}