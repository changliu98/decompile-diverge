static DWORD schannel_FreeCredentialsHandle(SecHandle *cred) {
  SecPkgCred_W *cred_w;
  if (!cred) return ((DWORD)0x80090001L);
  cred_w = (SecPkgCred_W *)sspi_SecureHandleGetLowerPointer(cred);
  if (!cred_w) return ((DWORD)0x80090001L);
  schannel_CredentialsFree(cred_w);
  return 0;
}