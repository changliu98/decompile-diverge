char *gcap_string(char *s, int caps) {
    if (caps & CEPH_CAP_GSHARED) {
        *s++ = 's';
    }
    if (caps & CEPH_CAP_GEXCL) {
        *s++ = 'x';
    }
    if (caps & CEPH_CAP_GCACHE) {
        *s++ = 'c';
    }
    if (caps & CEPH_CAP_GRD) {
        *s++ = 'r';
    }
    if (caps & CEPH_CAP_GWR) {
        *s++ = 'w';
    }
    if (caps & CEPH_CAP_GBUFFER) {
        *s++ = 'b';
    }
    if (caps & CEPH_CAP_GWREXTEND) {
        *s++ = 'a';
    }
    if (caps & CEPH_CAP_GLAZYIO) {
        *s++ = 'l';
    }
    
    return s;
}