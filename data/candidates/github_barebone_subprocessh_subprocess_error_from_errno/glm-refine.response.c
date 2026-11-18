subprocess_error_t __cdecl subprocess_error_from_errno(int error)
{
    switch ( error )
    {
        case EPERM:
            return SUBPROC_ERR_PERMISSION;
        case ENOENT:
            return SUBPROC_ERR_NOT_FOUND;
        case ENOMEM:
            return SUBPROC_ERR_RESOURCE;
        case EACCES:
            return SUBPROC_ERR_PERMISSION;
        case ENOTDIR:
            return SUBPROC_ERR_NOT_FOUND;
    }

    // Handles EINVAL (23) and ENOSYS (24)
    if ( error == EINVAL || error == ENOSYS )
        return SUBPROC_ERR_RESOURCE;

    return SUBPROC_ERR_UNKNOWN;
}