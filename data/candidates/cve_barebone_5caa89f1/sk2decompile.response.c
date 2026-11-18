void Perl_my_setenv(const char *name, const char *value) {
  int namelen, valuelen;
  char *env;
  namelen = strlen(name);
  if (!value) value = "";
  valuelen = strlen(value);
  env = vb_safesysmalloc(namelen + 1 + valuelen + 1);
  memcpy(env, name, namelen);
  env[namelen] = '=';
  memcpy(env + namelen + 1, value, valuelen);
  env[namelen + 1 + valuelen] = 0;
  vb_PerlEnv_putenv(env);
  free(env);
}