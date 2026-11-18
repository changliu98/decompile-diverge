int toml_value_string(char *buf, int bufsize, struct toml_node *node)
{
 int rc = -1;
 char *sp, *ep;
 int delim, slen;

 if (!node) {
  snprintf__bench(buf, bufsize, "NULL input");
  goto out;
 }

 switch (node->type) {
 case TOML_STRING:

  delim = node->u.str.quote;
  slen = strlen(node->u.str.text);
  sp = &node->u.str.text[0];
  ep = &node->u.str.text[slen-1];

  if (sp > ep || ep[0] != delim) {
   snprintf__bench(buf, bufsize, "invalid string");
   goto out;
  }

  if (delim == '\'')
   rc = norm_lit_str(sp, ep-sp, buf, bufsize, NULL, 0);
  else
   rc = norm_basic_str(sp, ep-sp, buf, bufsize, NULL, 0);

  break;

 case TOML_INTEGER:
  snprintf__bench(buf, bufsize, "%ld", node->u.integer.value);
  rc = 0;
  break;

 case TOML_BOOLEAN:
  snprintf__bench(buf, bufsize, "%s", node->u.boolean.value ? "true" : "false");
  rc = 0;
  break;

 case TOML_FLOAT:
  snprintf__bench(buf, bufsize, "%g", node->u.flt.value);
  rc = 0;
  break;

 case TOML_TIME:
  snprintf__bench(buf, bufsize, "%s", node->u.time.text);
  rc = 0;
  break;

 default:
  snprintf__bench(buf, bufsize, "invalid type");
  goto out;
 }
out:
 return rc;
}