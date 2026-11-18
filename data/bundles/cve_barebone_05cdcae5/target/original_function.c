ogs_pfcp_subnet_t *ogs_pfcp_subnet_add(
        const char *ipstr, const char *mask_or_numbits,
        const char *gateway, const char *dnn, const char *ifname)
{
    int rv;
    ogs_pfcp_dev_t *dev = NULL;
    ogs_pfcp_subnet_t *subnet = NULL;

    ogs_assert(ifname);

    dev = ogs_pfcp_dev_find_by_ifname(ifname);
    if (!dev)
        dev = ogs_pfcp_dev_add(ifname);
    ogs_assert(dev);

    pool_alloc(&subnet);
    ogs_assert(subnet);
    memset(subnet, 0, sizeof *subnet);

    subnet->family = AF_UNSPEC;
    subnet->dev = dev;

    if (ipstr && mask_or_numbits) {
        rv = ogs_ipsubnet(&subnet->gw, ipstr, NULL);
        ogs_assert(rv == OGS_OK);

        rv = ogs_ipsubnet(&subnet->sub, ipstr, mask_or_numbits);
        ogs_assert(rv == OGS_OK);

        subnet->family = subnet->gw.family;
    }

    if (gateway) {
        rv = ogs_ipsubnet(&subnet->gw, gateway, NULL);
        ogs_assert(rv == OGS_OK);
    }

    if (dnn)
        strcpy(subnet->dnn, dnn);   /* <<< VULNERABLE: no bounds check! */

    ogs_list_add(&subnet_list, subnet);

    return subnet;
}