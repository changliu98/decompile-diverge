static SECURITY_STATUS SEC_ENTRY schannel_FreeCredentialsHandle(PCredHandle phCredential)
{
	SCHANNEL_CREDENTIALS* credentials = nullptr;

	if (!phCredential)
		return SEC_E_INVALID_HANDLE;

	credentials = (SCHANNEL_CREDENTIALS*)sspi_SecureHandleGetLowerPointer(phCredential);

	if (!credentials)
		return SEC_E_INVALID_HANDLE;

	schannel_CredentialsFree(credentials);
	return SEC_E_OK;
}