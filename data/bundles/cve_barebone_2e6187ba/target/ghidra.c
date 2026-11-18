SECURITY_STATUS schannel_FreeCredentialsHandle(PCredHandle phCredential)

{
  SCHANNEL_CREDENTIALS *credentials_00;
  SCHANNEL_CREDENTIALS *credentials;
  PCredHandle phCredential_local;
  undefined8 local_10;
  
  if (phCredential == (PCredHandle)0x0) {
    local_10 = 0x80090301;
  }
  else {
    credentials_00 = sspi_SecureHandleGetLowerPointer(phCredential);
    if (credentials_00 == (SCHANNEL_CREDENTIALS *)0x0) {
      local_10 = 0x80090301;
    }
    else {
      schannel_CredentialsFree(credentials_00);
      local_10 = 0;
    }
  }
  return local_10;
}