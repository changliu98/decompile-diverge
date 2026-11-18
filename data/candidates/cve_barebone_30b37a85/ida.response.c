int __cdecl daemon_AuthUserPwd(char *username, char *password, char *errbuf)
{
  char *v3; // rax
  int *v4; // rax
  char *s1; // [rsp+8h] [rbp-38h]
  passwd *user; // [rsp+18h] [rbp-28h]

  user = getpwnam(username);
  if ( user && (s1 = user->pw_passwd, v3 = crypt(password, s1), !strcmp(s1, v3)) )
  {
    if ( setuid(user->pw_uid) )
    {
      v4 = __errno_location();
      pcap_fmt_errmsg_for_errno(errbuf, 0x100uLL, *v4, "setuid");
      return -1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    snprintf(errbuf, 0x100uLL, "Authentication failed: user name or password incorrect");
    return -1;
  }
}