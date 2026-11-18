ogs_pfcp_subnet_t *ogs_pfcp_subnet_add(const char *ip, const char *mask,
                                       const char *gw, const char *dns,
                                       const char *ifname) {
  ogs_pfcp_dev_t *dev = NULL;
  ogs_pfcp_subnet_t *subnet = NULL;
  int rv;
  do {
    if (!(ifname)) {
      fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "ifname", 180);
      abort();
    }
  } while (0);
  dev = ogs_pfcp_dev_find_by_ifname(ifname);
  if (!dev) dev = ogs_pfcp_dev_add(ifname);
  do {
    if (!(dev)) {
      fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "dev", 185);
      abort();
    }
  } while (0);
  pool_alloc(&subnet);
  do {
    if (!(subnet)) {
      fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "subnet", 188);
      abort();
    }
  } while (0);
  memset(subnet, 0, sizeof(ogs_pfcp_subnet_t));
  subnet->prefixlen = 0;
  subnet->dev = dev;
  if (ip && mask) {
    rv = ogs_ipsubnet(&subnet->ip, ip, NULL);
    do {
      if (!(rv == OGS_OK)) {
        fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "rv == OGS_OK",
                196);
        abort();
      }
    } while (0);
    rv = ogs_ipsubnet(&subnet->mask, ip, mask);
    do {
      if (!(rv == OGS_OK)) {
        fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "rv == OGS_OK",
                199);
        abort();
      }
    } while (0);
    subnet->prefixlen = subnet->ip.prefixlen;
  }
  if (gw) {
    rv = ogs_ipsubnet(&subnet->ip, gw, NULL);
    do {
      if (!(rv == OGS_OK)) {
        fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "rv == OGS_OK",
                206);
        abort();
      }
    } while (0);
  }
  if (dns) strcpy(subnet->dns, dns);
  ogs_list_add(&ogs_pfcp_subnet_list, subnet);
  return subnet;
}