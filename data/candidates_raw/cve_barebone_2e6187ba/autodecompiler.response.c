SECURITY_STATUS SECUR32_FreeCredentialsHandle(SEC_HANDLE phCredential)
{
    SECURITY_STATUS ret;
    SCHANNEL_CREDENTIALS *creds = NULL;

    if (!phCredential)
        ret = ((SECURITY_STATUS)0x80090301L);
    else
    {
        creds = sspi_SecureHandleGetLowerPointer(phCredential);
        if (!creds)
            ret = ((SECURITY_STATUS)0x80090301L);
        else
        {
            schannel_CredentialsFree(creds);
            ret = ((SECURITY_STATUS)0L);
        }
    }
    return ret;
}