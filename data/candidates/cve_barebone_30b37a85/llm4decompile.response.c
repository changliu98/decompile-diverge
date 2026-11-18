int
daemon_AuthUserPwd(const char *username, const char *password, char *errbuf)
{
	struct passwd *pwd;
	char *pwd_password;
	int err;

	/*
	 * Get the password entry for the user.
	 */
	pwd = getpwnam(username);
	if (pwd == NULL) {
		/*
		 * If that failed, report "Authentication failed: user
		 * name or password incorrect" to match the message
		 * reported if the password check failed.
		 */
		(void)snprintf(errbuf, 256,
		    "Authentication failed: user name or password incorrect");
		return (-1);
	}

	/*
	 * Check the password.
	 */
	pwd_password = crypt(password, pwd->pw_passwd);
	if (!strcmp(pwd->pw_passwd, pwd_password)) {
		/*
		 * Switch to that user.
		 */
		err = setuid(pwd->pw_uid);
		if (err) {
			pcap_fmt_errmsg_for_errno(errbuf, 256,
			    *__errno_location(), "setuid");
			return (-1);
		}

		/*
		 * All checks passed.
		 */
		return (0);
	}

	/*
	 * Report "Authentication failed: user name or password incorrect"
	 * to match the message reported if the getpwnam() failed.
	 */
	(void)snprintf(errbuf, 256,
	    "Authentication failed: user name or password incorrect");
	return (-1);
}