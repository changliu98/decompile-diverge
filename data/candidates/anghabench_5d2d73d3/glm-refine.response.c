void ecryptfs_get_versions(int *major, int *minor, int *file_version)
{
    /* 
     * Note: Unlike file_version, major and minor are unconditionally 
     * dereferenced, implying the caller must always provide valid pointers.
     */
    *major = ECRYPTFS_VERSION_MAJOR;
    *minor = ECRYPTFS_VERSION_MINOR;

    if (file_version != NULL)
        *file_version = ECRYPTFS_SUPPORTED_FILE_VERSION;
}