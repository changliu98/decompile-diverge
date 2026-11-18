void setrangeCommand(redisClient *c) {
 char *str = c->argv[3]->ptr;
 long offset;

 if (getLongFromObjectOrReply(c, c->argv[2], &offset, NULL) != 0)
  return;

 if (offset < 0) {
  addReplyError(c, "offset is out of range");
  return;
 }

 robj *o = lookupKeyWrite(c->db, c->argv[1]);

 if (o == NULL) {
  if (sdslen(str) == 0) {

   addReply(c, shared.czero);
   return;
  }
  else {
   if (checkStringLength(c, offset + sdslen(str)) != 0)
    return;

   o = createObject(0, _ZNSt3__212basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6resizeB8nn200000Em(0, offset + sdslen(str)));
   dbAdd(c->db, c->argv[1], o);
  }
 }
 else {
  if (checkType(c, o, 0) != 0)
   return;

  unsigned long olen = stringObjectLen(o);

  if (sdslen(str) == 0) {
   addReplyLongLong(c, olen);
   return;
  }
  else {
   if (checkStringLength(c, offset + sdslen(str)) != 0)
    return;

   o = dbUnshareStringValue(c->db, c->argv[1], o);
  }
 }

 if (sdslen(str) > 0) {
  char *p = o->ptr;
  p = sdsgrowzero(p, offset + sdslen(str));
  memcpy(p + offset, str, sdslen(str));

  signalModifiedKey(c, c->db, c->argv[1]);
  notifyKeyspaceEvent(8, "setrange", c->argv[1], c->db->id);
  server.dirty++;
 }

 addReplyLongLong(c, sdslen(o->ptr));
}