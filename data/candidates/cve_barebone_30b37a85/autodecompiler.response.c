static int
daemon_AuthUserPwd(char *user, char *password, char *errbuf)
{
 struct passwd *pw;
 char *crypt_password, *stored_password;
 int ret;





 pw = getpwnam(user);
 if (pw == NULL) {
  (void)snprintf(errbuf, 256,
      "Authentication failed: user name or password incorrect");
  ret = -1;
  goto out;
 }

 crypt_password = password;
 stored_password = pw->pw_passwd;





 if (strcmp(stored_password, crypt(crypt_password, stored_password)) != 0) {
  (void)snprintf(errbuf, 256,
      "Authentication failed: user name or password incorrect");
  ret = -1;
  goto out;
 }





 if (setuid(pw->pw_uid) != 0) {
  pcap_fmt_errmsg_for_errno(errbuf, 256, *___errno_location(),
      "setuid");
  ret = -1;
  goto out;
 }
# 109 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/SageAxcess/pcap-ndis6/refs/heads/dev-open/src/libpcap/pcap.c"
 ret = 0;

out:
 return (ret);
}