int daemon_AuthUserPwd(char *username,char *password,char *errbuf)

{
  char *salt;
  int iVar1;
  passwd *ppVar2;
  char *__s2;
  int *piVar3;
  char *user_password;
  passwd *user;
  char *errbuf_local;
  char *password_local;
  char *username_local;
  int local_c;
  
  ppVar2 = getpwnam(username);
  if (ppVar2 == (passwd *)0x0) {
    snprintf(errbuf,0x100,"Authentication failed: user name or password incorrect");
    local_c = -1;
  }
  else {
    salt = ppVar2->pw_passwd;
    __s2 = crypt(password,salt);
    iVar1 = strcmp(salt,__s2);
    if (iVar1 == 0) {
      iVar1 = setuid(ppVar2->pw_uid);
      if (iVar1 == 0) {
        local_c = 0;
      }
      else {
        piVar3 = __errno_location();
        pcap_fmt_errmsg_for_errno(errbuf,0x100,*piVar3,"setuid");
        local_c = -1;
      }
    }
    else {
      snprintf(errbuf,0x100,"Authentication failed: user name or password incorrect");
      local_c = -1;
    }
  }
  return local_c;
}