static char *limit_section(request_rec *r, char *dummy, char *args)
{
    char *e = strrchr(args, '>');
    char *w;
    int methnum;
    char *err;
    char *limited_methods;
    unsigned long limited = 0;
    unsigned long old_limited = r->allowed_methods;
    unsigned long negated = r->conf->limit_except_negated;
    char *negate;

    if (!e) {
 err = unclosed_directive(r);
 goto out;
    }

    limited_methods = apr_pstrmemdup(r->pool, args, e - args);

    if (limited_methods[0] == '\0') {
 err = missing_container_arg(r);
 goto out;
    }

    while (*limited_methods) {
 w = ap_getword_conf(r->pool, &limited_methods);
 methnum = ap_method_number_of(w);

 if ((methnum == 6) && !negated) {
     err = "TRACE cannot be controlled by <Limit>, see TraceEnable";
     goto out;
 }
 if (methnum == 26) {
     char *tmp = r->method;
     methnum = ap_method_register(tmp, apr_pstrdup(r->method, w));
 }
 limited |= (1L << methnum);
    }

    if (negated)
 limited = ~limited;

    if (!(old_limited & limited)) {
 err = apr_pstrcat(r->pool, r->conf->limit_except_section,
     "> directive excludes all methods", NULL);
 goto out;
    }

    if ((old_limited & limited) == old_limited) {
 err = apr_pstrcat(r->pool, r->conf->limit_except_section,
     "> directive specifies methods already excluded", NULL);
 goto out;
    }

    while ((negate = ap_getword_conf(r->pool, &args))) {
 r->allowed_methods &= limited;
 err = ap_walk_config(r->conf->limit_except, r, r->useragent_addr);
 r->allowed_methods = old_limited;
    }

out:
    return err;
}