int schannel_FreeCredentialsHandle(void *phCredential)
{
    struct sspi_cred *cred;
    if (phCredential == ((void *)0))
        return (SS_INVALID_HANDLE);
    cred = sspi_cred_from_handle(phCredential);
    if (cred == ((void *)0))
        return (SS_INVALID_HANDLE);
    sspi_cred_free_internal(cred);
    return (SS_OK);
}