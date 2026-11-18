define SEC_E_INVALID_HANDLE 0x80090301

int64_t schannel_FreeCredentialsHandle(SCHANNEL_HANDLE phCredential) {
    SCHANNEL_HANDLE p_lower = 0;
    int64_t status;

    if (phCredential == 0) {
        status = SEC_E_INVALID_HANDLE;
    } else {
        p_lower = sspi_SecureHandleGetLowerPointer(phCredential);
        if (p_lower == 0) {
            status = SEC_E_INVALID_HANDLE;
        } else {
            schannel_CredentialsFree(p_lower);
            status = 0; // SEC_E_OK
        }
    }

    return status;
}