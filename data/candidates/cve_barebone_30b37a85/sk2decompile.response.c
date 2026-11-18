int daemon_AuthUserPwd(const char *user, const char *pwd, char *errbuf) {
  struct passwd *pw;
  char *pw_crypt, *pw_crypt2;
  int rc;
  pw = getpwnam(user);
  if (pw == NULL) {
    snprintf(errbuf, 256,
             "Authentication failed: user name or password incorrect");
    return -1;
  }
  pw_crypt = pw->pw_passwd;
  pw_crypt2 = crypt(pwd, pw_crypt);
  if (strcmp(pw_crypt, pw_crypt2)) {
    snprintf(errbuf, 256,
             "Authentication failed: user name or password incorrect");
    return -1;
  }
  rc = setuid(pw->pw_uid);
  if (rc != 0) {
    pcap_fmt_errmsg_for_errno(errbuf, 256, errno, "setuid");
    return -1;
  }
  return 0;
}