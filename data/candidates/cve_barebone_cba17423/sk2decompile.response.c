static const char *ap_limit_section(ap_directive_t *d, const char *param,
                                    const char *value) {
  const char *end = strrchr(value, '>');
  const char *exclude = d->conf->exclude;
  unsigned long mask = 0;
  unsigned long old_mask = d->mask;
  unsigned long new_mask;
  const char *methods;
  const char *method;
  int method_number;
  const char *rval;
  if (!end) return unclosed_directive(d);
  methods = apr_pstrmemdup(d->p, value, end - value);
  if (!*methods) return missing_container_arg(d);
  while (*methods) {
    method = ap_getword_conf(d->p, &methods);
    method_number = ap_method_number_of(method);
    if (method_number == 6 && !exclude)
      return "TRACE cannot be controlled by <Limit>, see TraceEnable";
    if (method_number == 26) {
      apr_pool_t *p = d->p;
      method_number = ap_method_register(p, apr_pstrdup(p, method));
    }
    mask |= 1UL << method_number;
  }
  new_mask = exclude ? ~mask : mask;
  if (!(old_mask & new_mask))
    return apr_pstrcat(d->p, d->conf->name,
                       "> directive excludes all methods", NULL);
  if (old_mask == (old_mask & new_mask))
    return apr_pstrcat(d->p, d->conf->name,
                       "> directive specifies methods already excluded", NULL);
  d->mask &= new_mask;
  rval = ap_walk_config(d->c->config_file, d, d->next);
  d->mask = old_mask;
  return rval;
}