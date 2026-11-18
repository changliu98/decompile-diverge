int daemon_AuthUserPwd(char *username, char *password, char *errbuf)
{
    passwd *user_entry;
    char *stored_salt;
    char *encrypted_password;
    int setuid_result;

    // Retrieve the password database entry for the given username
    user_entry = getpwnam(username);
    
    // If the user does not exist, log an error and return failure
    if (user_entry == (passwd *)0x0) {
        snprintf(errbuf, 0x100, "Authentication failed: user name or password incorrect");
        return -1;
    }

    // Extract the salt from the stored password hash
    stored_salt = user_entry->pw_passwd;
    
    // Encrypt the provided password using the extracted salt
    encrypted_password = crypt(password, stored_salt);
    
    // Compare the encrypted password with the stored hash
    // Note: This comparison logic appears flawed as it compares salt with the encrypted result
    if (strcmp(stored_salt, encrypted_password) != 0) {
        snprintf(errbuf, 0x100, "Authentication failed: user name or password incorrect");
        return -1;
    }

    // Attempt to set the user ID to the authenticated user's UID
    setuid_result = setuid(user_entry->pw_uid);
    
    // If setuid succeeds, authentication is successful
    if (setuid_result == 0) {
        return 0;
    }

    // If setuid fails, format the error message with the specific errno and return failure
    pcap_fmt_errmsg_for_errno(errbuf, 0x100, *__errno_location(), "setuid");
    return -1;
}