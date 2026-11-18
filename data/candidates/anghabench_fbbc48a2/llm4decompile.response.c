char *gcap_string(char *s, int cap)
{
	if (cap & CEPH_CAP_GSHARED)
		*s++ = 's';
	if (cap & CEPH_CAP_GEXCL)
		*s++ = 'x';
	if (cap & CEPH_CAP_GCACHE)
		*s++ = 'c';
	if (cap & CEPH_CAP_GRD)
		*s++ = 'r';
	if (cap & CEPH_CAP_GWR)
		*s++ = 'w';
	if (cap & CEPH_CAP_GBUFFER)
		*s++ = 'b';
	if (cap & CEPH_CAP_GWREXTEND)
		*s++ = 'a';
	if (cap & CEPH_CAP_GLAZYIO)
		*s++ = 'l';
	return s;
}