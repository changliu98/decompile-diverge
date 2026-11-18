char *__cdecl gcap_string(char *s, int c)
{
  char *sa = s;

  if ( (CEPH_CAP_GSHARED & c) != 0 )
    *sa++ = 's';

  if ( (CEPH_CAP_GEXCL & c) != 0 )
    *sa++ = 'x';

  if ( (CEPH_CAP_GCACHE & c) != 0 )
    *sa++ = 'c';

  if ( (CEPH_CAP_GRD & c) != 0 )
    *sa++ = 'r';

  if ( (CEPH_CAP_GWR & c) != 0 )
    *sa++ = 'w';

  if ( (CEPH_CAP_GBUFFER & c) != 0 )
    *sa++ = 'b';

  if ( (CEPH_CAP_GWREXTEND & c) != 0 )
    *sa++ = 'a';

  if ( (CEPH_CAP_GLAZYIO & c) != 0 )
    *sa++ = 'l';

  return sa;
}