void ecryptfs_get_versions(int *major, int *minor, int *file_version)
{
  *major = ECRYPTFS_VERSION_MAJOR;
  *minor = ECRYPTFS_VERSION_MINOR;
  if (file_version)
    *file_version = ECRYPTFS_SUPPORTED_FILE_VERSION;
}