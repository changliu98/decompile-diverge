char * gcap_string(char *s,int c)

{
  int c_local;
  char *s_local;
  
  s_local = s;
  if ((c & CEPH_CAP_GSHARED) != 0) {
    s_local = s + 1;
    *s = 's';
  }
  if ((c & CEPH_CAP_GEXCL) != 0) {
    *s_local = 'x';
    s_local = s_local + 1;
  }
  if ((c & CEPH_CAP_GCACHE) != 0) {
    *s_local = 'c';
    s_local = s_local + 1;
  }
  if ((c & CEPH_CAP_GRD) != 0) {
    *s_local = 'r';
    s_local = s_local + 1;
  }
  if ((c & CEPH_CAP_GWR) != 0) {
    *s_local = 'w';
    s_local = s_local + 1;
  }
  if ((c & CEPH_CAP_GBUFFER) != 0) {
    *s_local = 'b';
    s_local = s_local + 1;
  }
  if ((c & CEPH_CAP_GWREXTEND) != 0) {
    *s_local = 'a';
    s_local = s_local + 1;
  }
  if ((c & CEPH_CAP_GLAZYIO) != 0) {
    *s_local = 'l';
    s_local = s_local + 1;
  }
  return s_local;
}