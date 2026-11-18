void __cdecl setrangeCommand(client *c)
{
  char *value = *(char **)(*((_QWORD *)c->argv + 3) + 8LL);
  long offset;
  if ( !getLongFromObjectOrReply(c, c->argv[2], &offset, 0LL) )
  {
    if ( offset < 0 )
    {
      addReplyError(c, "offset is out of range");
      return;
    }

    robj *o = lookupKeyWrite(c->db, c->argv[1]);
    if ( o )
    {
      if ( checkType(c, o, 0) )
        return;

      __int64 olen = stringObjectLen(o);
      if ( !sdslen(value) )
      {
        addReplyLongLong(c, olen);
        return;
      }

      size_t v4 = sdslen(value);
      if ( !checkStringLength(c, v4 + offset) )
      {
        o = dbUnshareStringValue(c->db, c->argv[1], o);
        goto LABEL_14;
      }
    }
    else
    {
      if ( !sdslen(value) )
      {
        addReply(c, shared);
        return;
      }

      size_t v1 = sdslen(value);
      if ( !checkStringLength(c, v1 + offset) )
      {
        size_t v2 = sdslen(value);
        sds v3 = std::string::resize[abi:nn200000](0LL, v2 + offset);
        o = createObject(0, v3);
        dbAdd(c->db, c->argv[1], o);

LABEL_14:
        if ( sdslen(value) )
        {
          char *s = (char *)o->ptr;
          size_t v5 = sdslen(value);
          sds v6 = sdsgrowzero(s, v5 + offset);
          o->ptr = v6;
          
          char *dest = (char *)o->ptr + offset;
          size_t v7 = sdslen(value);
          memcpy(dest, value, v7);
          
          signalModifiedKey(c, c->db, c->argv[1]);
          notifyKeyspaceEvent(8, "setrange", c->argv[1], c->db->id);
          ++qword_50C8;
        }
        addReplyLongLong(c, sdslen((const sds)o->ptr));
      }
    }
  }
}