define SEC_E_INVALID_HANDLE_VAL 0x80090301

SECURITY_STATUS __cdecl schannel_FreeCredentialsHandle(PCredHandle phCredential)
{
    SCHANNEL_CREDENTIALS *pCredentials;

    if (!phCredential)
        return SEC_E_INVALID_HANDLE_VAL;

    // Extracts the lower 64-bit pointer from the SSPI handle structure
    pCredentials = (SCHANNEL_CREDENTIALS *)sspi_SecureHandleGetLowerPointer(phCredential);
    
    if (!pCredentials)
        return SEC_E_INVALID_HANDLE_VAL;

    schannel_CredentialsFree(pCredentials);
    
    // 0x00000000: SEC_E_OK
    return SEC_E_OK;
}