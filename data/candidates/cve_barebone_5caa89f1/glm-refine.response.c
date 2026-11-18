void __cdecl Perl_my_setenv(const char *nam, const char *val)
{
  const char *env_val = val ? val : "";
  
  size_t nam_len = strlen(nam);
  size_t val_len = strlen(env_val);
  
  // Allocate space for "nam=val\0"
  char *env_str = (char *)vb_safesysmalloc(nam_len + val_len + 2);
  
  // Construct the environment string: <name>=<value>
  memcpy(env_str, nam, nam_len);
  env_str[nam_len] = '='; // ASCII 61
  memcpy(env_str + nam_len + 1, env_val, val_len);
  env_str[nam_len + val_len + 1] = '\0';
  
  // Set the environment variable and free the allocated buffer
  vb_PerlEnv_putenv(env_str);
  free(env_str);
}