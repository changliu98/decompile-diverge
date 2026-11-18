void ecryptfs_get_versions(int *major,int *minor,int *file_version)

{
  int *file_version_local;
  int *minor_local;
  int *major_local;
  
  *major = ECRYPTFS_VERSION_MAJOR;
  *minor = ECRYPTFS_VERSION_MINOR;
  if (file_version != (int *)0x0) {
    *file_version = ECRYPTFS_SUPPORTED_FILE_VERSION;
  }
  return;
}