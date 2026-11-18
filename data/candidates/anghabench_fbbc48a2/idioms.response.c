char *gcap_string(char *out, int cap)
{
 if (CEPH_CAP_GSHARED & cap)
  *out++ = 's';
 if (CEPH_CAP_GEXCL & cap)
  *out++ = 'x';
 if (CEPH_CAP_GCACHE & cap)
  *out++ = 'c';
 if (CEPH_CAP_GRD & cap)
  *out++ = 'r';
 if (CEPH_CAP_GWR & cap)
  *out++ = 'w';
 if (CEPH_CAP_GBUFFER & cap)
  *out++ = 'b';
 if (CEPH_CAP_GWREXTEND & cap)
  *out++ = 'a';
 if (CEPH_CAP_GLAZYIO & cap)
  *out++ = 'l';
 return out;
}