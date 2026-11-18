void setrangeCommand(client *c)

{
  sds s;
  void *pvVar1;
  long lVar2;
  client *pcVar3;
  int iVar4;
  size_t sVar5;
  sds pcVar6;
  size_t sVar7;
  size_t olen;
  sds value;
  long offset;
  robj *o;
  client *c_local;
  
  s = c->argv[3]->ptr;
  c_local = c;
  iVar4 = getLongFromObjectOrReply(c,c->argv[2],&offset,(char *)0x0);
  if (iVar4 == 0) {
    if (offset < 0) {
      addReplyError(c_local,"offset is out of range");
    }
    else {
      o = lookupKeyWrite(c_local->db,c_local->argv[1]);
      if (o == (robj *)0x0) {
        sVar5 = sdslen(s);
        pcVar3 = c_local;
        lVar2 = offset;
        if (sVar5 == 0) {
          addReply(c_local,shared.czero);
          return;
        }
        sVar5 = sdslen(s);
        iVar4 = checkStringLength(pcVar3,lVar2 + sVar5);
        lVar2 = offset;
        if (iVar4 != 0) {
          return;
        }
        sVar5 = sdslen(s);
        pcVar6 = sdsnewlen((void *)0x0,lVar2 + sVar5);
        o = createObject(0,pcVar6);
        dbAdd(c_local->db,c_local->argv[1],o);
      }
      else {
        iVar4 = checkType(c_local,o,0);
        if (iVar4 != 0) {
          return;
        }
        sVar5 = stringObjectLen(o);
        sVar7 = sdslen(s);
        pcVar3 = c_local;
        lVar2 = offset;
        if (sVar7 == 0) {
          addReplyLongLong(c_local,sVar5);
          return;
        }
        sVar5 = sdslen(s);
        iVar4 = checkStringLength(pcVar3,lVar2 + sVar5);
        if (iVar4 != 0) {
          return;
        }
        o = dbUnshareStringValue(c_local->db,c_local->argv[1],o);
      }
      sVar5 = sdslen(s);
      lVar2 = offset;
      if (sVar5 != 0) {
        pcVar6 = o->ptr;
        sVar5 = sdslen(s);
        pcVar6 = sdsgrowzero(pcVar6,lVar2 + sVar5);
        o->ptr = pcVar6;
        pvVar1 = o->ptr;
        sVar5 = sdslen(s);
        memcpy((void *)((long)pvVar1 + offset),s,sVar5);
        signalModifiedKey(c_local,c_local->db,c_local->argv[1]);
        notifyKeyspaceEvent(8,"setrange",c_local->argv[1],c_local->db->id);
        server.dirty = server.dirty + 1;
      }
      pcVar3 = c_local;
      sVar5 = sdslen(o->ptr);
      addReplyLongLong(pcVar3,sVar5);
    }
  }
  return;
}