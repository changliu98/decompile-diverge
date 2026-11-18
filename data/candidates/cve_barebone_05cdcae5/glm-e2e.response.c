ogs_pfcp_subnet_t *ogs_pfcp_subnet_add(const char *ipstr, const char *mask_or_numbits,
                                       const char *range, const char *apn, const char *ifname) {
    ogs_pfcp_dev_t *dev = NULL;
    ogs_pfcp_subnet_t *subnet = NULL;
    int rv;

    if (ifname == NULL) {
        fprintf(stderr, "assertion failed: ifname");
        abort();
    }

    dev = ogs_pfcp_dev_find_by_ifname(ifname);
    if (dev == NULL) {
        dev = ogs_pfcp_dev_add(ifname);
    }

    if (dev == NULL) {
        fprintf(stderr, "assertion failed: dev");
        abort();
    }

    pool_alloc(&subnet);
    if (subnet == NULL) {
        fprintf(stderr, "assertion failed: subnet");
        abort();
    }

    memset(subnet, 0, 0x1d8);
    subnet->family = 0;
    subnet->dev = dev;

    if (ipstr != NULL && mask_or_numbits != NULL) {
        rv = ogs_ipsubnet(&subnet->gw, ipstr, NULL);
        if (rv != 0) {
            fprintf(stderr, "assertion failed: rv == 0");
            abort();
        }

        rv = ogs_ipsubnet(&subnet->sub, ipstr, mask_or_numbits);
        if (rv != 0) {
            fprintf(stderr, "assertion failed: rv == 0");
            abort();
        }

        subnet->family = subnet->gw.family;
    }

    if (range != NULL) {
        rv = ogs_ipsubnet(&subnet->range, range, NULL);
        if (rv != 0) {
            fprintf(stderr, "assertion failed: rv == 0");
            abort();
        }
    }

    if (apn != NULL) {
        strcpy(subnet->apn, apn);
    }

    ogs_list_add(&subnet_list, subnet);

    return subnet;
}