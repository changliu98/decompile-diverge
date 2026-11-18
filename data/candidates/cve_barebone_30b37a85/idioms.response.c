int daemon_AuthUserPwd(char *user, char *pass, char *errbuf)
{
  struct passwd *pw;
  char *passhash;
  if ((pw = getpwnam(user)) == ((void *)0))
  {
    return -1;
  }
  passhash = pw->pw_passwd;
  if (check_password(pass, passhash) == 0 ||
      check_password(passhash,
        crypt(pass, passhash)) == 0)
  {
    if (is_root(pw->pw_uid))
    {
      set_err(errbuf, 256, get_err(), "setuid");
      return -1;
    }
    return 0;
  }
  set_err(errbuf, 256, "Authentication failed: user name or password incorrect");
  return -1;
}