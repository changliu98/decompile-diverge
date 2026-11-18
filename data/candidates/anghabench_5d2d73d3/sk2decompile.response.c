void ecryptfs_get_versions(int *major, int *minor, int *micro) {
  *major = ECRYPTFS_VERSION_MAJOR;
  *minor = ECRYPTFS_VERSION_MINOR;
  if (micro) *micro = ECRYPTFS_VERSION_MICRO;
}