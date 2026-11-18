ogs_pfcp_subnet_t *ogs_pfcp_subnet_add(
        char *network, char *mask, char *gateway,
        char *dnn, char *ifname)
{
    int rv;
    ogs_pfcp_dev_t *dev = NULL;
    ogs_pfcp_subnet_t *subnet = NULL;

    ogs_assert(ifname);

    while (1) {

        dev = ogs_pfcp_dev_find_by_ifname(ifname);
        if (!dev) {
            dev = ogs_pfcp_dev_add(ifname);
        }

        break;
    }

    ogs_assert(dev);

    do { (subnet) = pool_alloc(sizeof(ogs_pfcp_subnet_t)); ogs_assert((subnet) != NULL); } while(0);
    memset(subnet, 0, sizeof(ogs_pfcp_subnet_t));

    subnet->dev = dev;

    if (network && mask) {
        rv = ogs_ipsubnet(&subnet->network, network, mask);
        ogs_assert(rv == OGS_OK);
    } else {
        subnet->network.family = 0;
    }

    if (gateway) {
        rv = ogs_ipsubnet(&subnet->gateway, gateway, NULL);
        ogs_assert(rv == OGS_OK);
    } else {
        subnet->gateway.family = 0;
    }

    if (dnn) {
        strcpy(&subnet->dnn[0], dnn);
    }

    ogs_list_add(&subnet_list, subnet);

    return subnet;
}