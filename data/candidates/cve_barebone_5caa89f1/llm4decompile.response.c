void Perl_my_setenv(const char *nam, const char *val)
{
    size_t nlen = strlen(nam);
    size_t vlen = strlen(val ? val : "");
    char *envstr = vb_safesysmalloc(nlen + 1 + vlen + 1);
    memcpy(envstr, nam, nlen);
    envstr[nlen] = '=';
    memcpy(envstr + nlen + 1, val ? val : "", vlen);
    envstr[nlen + 1 + vlen] = '\0';
    vb_PerlEnv_putenv(envstr);
    free(envstr);
}