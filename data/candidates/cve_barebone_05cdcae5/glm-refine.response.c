ogs_pfcp_subnet_t *__cdecl ogs_pfcp_subnet_add(
        const char *ipstr,
        const char *mask_or_numbits,
        const char *gateway,
        const char *dnn,
        const char *ifname)
{
  ogs_pfcp_subnet_t *subnet = NULL;
  ogs_pfcp_dev_t *dev = NULL;
  int rv;

  // IDA often generates redundant local aliases for parameters; they have been removed.
  
  if (!ifname) {
    fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "ifname", 180);
    abort();
  }

  dev = ogs_pfcp_dev_find_by_ifname(ifname);
  if (!dev)
    dev = ogs_pfcp_dev_add(ifname);

  if (!dev) {
    fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "dev", 185);
    abort();
  }

  pool_alloc(&subnet);
  if (!subnet) {
    fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "subnet", 188);
    abort();
  }

  memset(subnet, 0, sizeof(ogs_pfcp_subnet_t));
  subnet->family = 0;
  subnet->dev = dev;

  if (ipstr && mask_or_numbits) {
    rv = ogs_ipsubnet(&subnet->gw, ipstr, NULL);
    if (rv) {
      fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "rv == OGS_OK", 196);
      abort();
    }

    rv = ogs_ipsubnet(&subnet->sub, ipstr, mask_or_numbits);
    if (rv) {
      fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "rv == OGS_OK", 199);
      abort();
    }

    subnet->family = subnet->gw.family;
  }

  if (gateway) {
    rv = ogs_ipsubnet(&subnet->gw, gateway, NULL);
    if (rv) {
      fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "rv == OGS_OK", 206);
      abort();
    }
  }

  if (dnn)
    strcpy(subnet->dnn, dnn);

  ogs_list_add(&subnet_list, subnet);

  return subnet;
}