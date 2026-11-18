void Perl_my_setenv(const char *name, const char *value) {
    size_t name_len = strlen(name);
    
    // If value is NULL, default it to an empty string
    if (value == NULL) {
        value = "";
    }
    
    size_t value_len = strlen(value);
    
    // Allocate memory for "name=value\0"
    char *envstr = (char *)vb_safesysmalloc(name_len + value_len + 2);
    
    // Copy the name to the newly allocated string
    memcpy(envstr, name, name_len);
    
    // Append the '=' character
    envstr[name_len] = '=';
    
    // Append the value
    memcpy(envstr + name_len + 1, value, value_len);
    
    // Null-terminate the string
    envstr[name_len + 1 + value_len] = '\0';
    
    // Put the string into the environment
    vb_PerlEnv_putenv(envstr);
    
    // Free the allocated string
    free(envstr);
}