void setrangeCommand(redisClient *c) {
  long offset;
  robj *o;
  char *value = c->argv[3]->ptr;
  if (getLongFromObjectOrReply(c, c->argv[2], &offset, NULL) != 0) return;
  if (offset < 0) {
    addReplyError(c, "offset is out of range");
    return;
  }
  o = lookupKeyWrite(c->db, c->argv[1]);
  if (o != NULL) {
    long curlen;
    if (checkType(c, o, 0)) return;
    curlen = stringObjectLen(o);
    if (sdslen(value) == 0) {
      addReplyLongLong(c, curlen);
      return;
    }
    if (checkStringLength(c, offset + sdslen(value)) != 0) return;
    o = dbUnshareStringValue(c->db, c->argv[1], o);
  } else {
    if (sdslen(value) == 0) {
      addReply(c, shared.czero);
      return;
    }
    if (checkStringLength(c, offset + sdslen(value)) != 0) return;
    o = createObject(0, std::string().resize(offset + sdslen(value), '\0'));
    dbAdd(c->db, c->argv[1], o);
  }
  if (sdslen(value) != 0) {
    o->ptr = sdsgrowzero(o->ptr, offset + sdslen(value));
    memcpy(o->ptr + offset, value, sdslen(value));
    signalModifiedKey(c, c->db, c->argv[1]);
    notifyKeyspaceEvent(8, "setrange", c->argv[1], c->db->id);
    server.dirty++;
  }
  addReplyLongLong(c, sdslen(o->ptr));
}