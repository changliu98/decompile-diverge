char *__cdecl gcap_string(char *s, int c)
{
  char *v2; // rax
  char *v3; // rax
  char *v4; // rax
  char *v5; // rax
  char *v6; // rax
  char *v7; // rax
  char *v8; // rax
  char *sa; // [rsp+4h] [rbp-8h]

  sa = s;
  if ( (CEPH_CAP_GSHARED & c) != 0 )
  {
    sa = s + 1;
    *s = 115;
  }
  if ( (CEPH_CAP_GEXCL & c) != 0 )
  {
    v2 = sa++;
    *v2 = 120;
  }
  if ( (CEPH_CAP_GCACHE & c) != 0 )
  {
    v3 = sa++;
    *v3 = 99;
  }
  if ( (CEPH_CAP_GRD & c) != 0 )
  {
    v4 = sa++;
    *v4 = 114;
  }
  if ( (CEPH_CAP_GWR & c) != 0 )
  {
    v5 = sa++;
    *v5 = 119;
  }
  if ( (CEPH_CAP_GBUFFER & c) != 0 )
  {
    v6 = sa++;
    *v6 = 98;
  }
  if ( (CEPH_CAP_GWREXTEND & c) != 0 )
  {
    v7 = sa++;
    *v7 = 97;
  }
  if ( (CEPH_CAP_GLAZYIO & c) != 0 )
  {
    v8 = sa++;
    *v8 = 108;
  }
  return sa;
}