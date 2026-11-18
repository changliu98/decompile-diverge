char *gcap_string(char *str, int mode)
{
	if (mode & CEPH_CAP_GSHARED)
		*str++ = 's';
	if (mode & CEPH_CAP_GEXCL)
		*str++ = 'x';
	if (mode & CEPH_CAP_GCACHE)
		*str++ = 'c';
	if (mode & CEPH_CAP_GRD)
		*str++ = 'r';
	if (mode & CEPH_CAP_GWR)
		*str++ = 'w';
	if (mode & CEPH_CAP_GBUFFER)
		*str++ = 'b';
	if (mode & CEPH_CAP_GWREXTEND)
		*str++ = 'a';
	if (mode & CEPH_CAP_GLAZYIO)
		*str++ = 'l';
	return str;
}