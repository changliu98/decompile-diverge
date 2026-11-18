int daemon_AuthUserPwd(const char *username, const char *password, char *errbuf) {
    struct passwd *pw;
    char *encrypted_pw;
    char *correct_pw;
    int ret;
    int errnum;
    char *errbuf_ptr;

    pw = getpwnam(username);
    if (pw == NULL) {
        snprintf(errbuf, 0x100, "%s", "User not found"); // String at 0x2080
        ret = -1;
        return ret;
    }

    encrypted_pw = pw->pw_passwd;
    correct_pw = encrypted_pw;
    
    encrypted_pw = crypt(password, encrypted_pw);
    if (strcmp(correct_pw, encrypted_pw) != 0) {
        snprintf(errbuf, 0x100, "%s", "User not found"); // String at 0x2080
        ret = -1;
        return ret;
    }

    if (setuid(pw->pw_uid) != 0) {
        errbuf_ptr = errbuf;
        errnum = errno;
        pcap_fmt_errmsg_for_errno(errbuf_ptr, 0x100, errnum, "%s", "setuid"); // String at 0x20b7
        ret = -1;
        return ret;
    }

    ret = 0;
    return ret;
}