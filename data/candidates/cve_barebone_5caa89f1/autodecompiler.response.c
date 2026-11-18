void Perl_my_setenv(char *name, char *value)
{
 int namelen = strlen(name);
 if (!value) value = "";
 int valuelen = strlen(value);

 char *buf = (char *)vb_safesysmalloc(namelen + valuelen + 2);
 memcpy(buf, name, namelen);
 buf[namelen] = '=';
 memcpy(buf + namelen + 1, value, valuelen);
 buf[namelen + 1 + valuelen] = '\0';

 vb_PerlEnv_putenv(buf);

 free(buf);
}