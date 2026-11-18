SECURITY_STATUS schannel_FreeCredentialsHandle(PCredHandle phCredential)
{
    SCHANNEL_CREDENTIALS *credentials;

    if (!phCredential)
        return ((SECURITY_STATUS)0x80090301L);

    credentials = sspi_SecureHandleGetLowerPointer(phCredential);
    if (!credentials)
        return ((SECURITY_STATUS)0x80090301L);

    schannel_CredentialsFree(credentials);

    return 0;
}