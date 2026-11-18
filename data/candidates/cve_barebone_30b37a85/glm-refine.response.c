int __cdecl daemon_AuthUserPwd(char *username, char *password, char *errbuf)
{
  struct passwd *user;
  char *encrypted_pwd;
  char *stored_pwd;

  user = getpwnam(username);
  if ( !user )
  {
    snprintf(errbuf, 0x100uLL, "Authentication failed: user name or password incorrect");
    return -1;
  }

  stored_pwd = user->pw_passwd;
  encrypted_pwd = crypt(password, stored_pwd);
  
  if ( !stored_pwd || !encrypted_pwd || strcmp(stored_pwd, encrypted_pwd) != 0 )
  {
    snprintf(errbuf, 0x100uLL, "Authentication failed: user name or password incorrect");
    return -1;
  }

  if ( setuid(user->pw_uid) != 0 )
  {
    pcap_fmt_errmsg_for_errno(errbuf, 0x100uLL, *__errno_location(), "setuid");
    return -1;
  }

  return 0;
}