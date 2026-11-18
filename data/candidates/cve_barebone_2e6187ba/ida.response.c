SECURITY_STATUS __cdecl schannel_FreeCredentialsHandle(PCredHandle phCredential)
{
  SCHANNEL_CREDENTIALS *credentials; // [rsp+8h] [rbp-18h]

  if ( !phCredential )
    return 2148074241LL;
  credentials = (SCHANNEL_CREDENTIALS *)sspi_SecureHandleGetLowerPointer(phCredential);
  if ( !credentials )
    return 2148074241LL;
  schannel_CredentialsFree(credentials);
  return 0LL;
}