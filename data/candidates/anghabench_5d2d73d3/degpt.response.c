void ecryptfs_get_versions(int *out_major, int *out_minor, int *out_file_version)
{
	/* Set the major version number */
	*out_major = ECRYPTFS_VERSION_MAJOR;
	/* Set the minor version number */
	*out_minor = ECRYPTFS_VERSION_MINOR;
	/* If the file_version pointer is valid, set the supported file version */
	if (out_file_version)
		*out_file_version = ECRYPTFS_SUPPORTED_FILE_VERSION;
}