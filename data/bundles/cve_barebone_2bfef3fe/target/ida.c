void __cdecl setrangeCommand(client *c)
{
  size_t v1; // rax
  size_t v2; // rax
  sds v3; // rax
  size_t v4; // rax
  size_t v5; // rax
  sds v6; // rax
  size_t v7; // rax
  __int64 v8; // rax
  client *v9; // [rsp+8h] [rbp-78h]
  long v10; // [rsp+10h] [rbp-70h]
  char *s; // [rsp+18h] [rbp-68h]
  char *dest; // [rsp+20h] [rbp-60h]
  long v13; // [rsp+30h] [rbp-50h]
  client *v14; // [rsp+38h] [rbp-48h]
  long v15; // [rsp+40h] [rbp-40h]
  long v16; // [rsp+48h] [rbp-38h]
  client *v17; // [rsp+50h] [rbp-30h]
  __int64 olen; // [rsp+58h] [rbp-28h]
  char *value; // [rsp+60h] [rbp-20h]
  long offset; // [rsp+68h] [rbp-18h] BYREF
  robj *o; // [rsp+70h] [rbp-10h]
  client *ca; // [rsp+78h] [rbp-8h]

  ca = c;
  value = *(char **)(*((_QWORD *)c->argv + 3) + 8LL);
  if ( getLongFromObjectOrReply(c, c->argv[2], &offset, 0LL) )
    return;
  if ( offset < 0 )
  {
    addReplyError(ca, "offset is out of range");
    return;
  }
  o = lookupKeyWrite(ca->db, ca->argv[1]);
  if ( o )
  {
    if ( checkType(ca, o, 0) )
      return;
    olen = stringObjectLen(o);
    if ( !sdslen(value) )
    {
      addReplyLongLong(ca, olen);
      return;
    }
    v14 = ca;
    v13 = offset;
    v4 = sdslen(value);
    if ( !checkStringLength(v14, v4 + v13) )
    {
      o = dbUnshareStringValue(ca->db, ca->argv[1], o);
      goto LABEL_14;
    }
  }
  else
  {
    if ( !sdslen(value) )
    {
      addReply(ca, shared);
      return;
    }
    v17 = ca;
    v16 = offset;
    v1 = sdslen(value);
    if ( !checkStringLength(v17, v1 + v16) )
    {
      v15 = offset;
      v2 = sdslen(value);
      v3 = std::string::resize[abi:nn200000](0LL, v2 + v15);
      o = createObject(0, v3);
      dbAdd(ca->db, ca->argv[1], o);
LABEL_14:
      if ( sdslen(value) )
      {
        s = (char *)o->ptr;
        v10 = offset;
        v5 = sdslen(value);
        v6 = sdsgrowzero(s, v5 + v10);
        o->ptr = v6;
        dest = (char *)o->ptr + offset;
        v7 = sdslen(value);
        memcpy(dest, value, v7);
        signalModifiedKey(ca, ca->db, ca->argv[1]);
        notifyKeyspaceEvent(8, "setrange", ca->argv[1], ca->db->id);
        ++qword_50C8;
      }
      v9 = ca;
      v8 = sdslen((const sds)o->ptr);
      addReplyLongLong(v9, v8);
    }
  }
}