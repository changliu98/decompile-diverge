int unix_socketpair(int d,int type,int protocol,int *sv)

{
  int iVar1;
  int *sv_local;
  int protocol_local;
  int type_local;
  int d_local;
  
  iVar1 = socketpair(d,type,protocol,sv);
  return iVar1;
}