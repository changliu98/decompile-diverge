define NOTIFY_STRING 8

void setrangeCommand(struct Client *c) {
    long long offset;
    void *o = NULL;
    char *value;
    long long o_len;
    char *cp;
    char *cptr;

    // c->argv[2]->ptr
    value = ((struct Object *)c->argv[2])->sds;

    // getLongFromObjectOrReply(c, c->argv[1], &offset, NULL)
    if (getLongFromObjectOrReply(c, c->argv[1], &offset, NULL) != 0) {
        return;
    }

    if (offset < 0) {
        addReplyError(c, "value is not a valid integer");
        return;
    }

    o = lookupKeyWrite(c->db, c->argv[1]);

    if (o == NULL) {
        if (sdslen(value) == 0) {
            addReply(c, shared);
            return;
        }

        if (checkStringLength(c, offset, sdslen(value)) != 0) {
            return;
        }

        o = createObject(OBJ_STRING, sdsnewlen("", offset + sdslen(value)));
        dbAdd(c->db, c->argv[1], o);
    } else {
        if (checkType(c, o, OBJ_STRING) != 0) {
            return;
        }

        o_len = stringObjectLen(o);

        if (sdslen(value) == 0) {
            addReplyLongLong(c, o_len);
            return;
        }

        if (checkStringLength(c, offset, sdslen(value)) != 0) {
            return;
        }

        o = dbUnshareStringValue(c->db, c->argv[1], o);
    }

    if (sdslen(value) > 0) {
        // ((struct Object *)o)->sds = sdsgrowzero(((struct Object *)o)->sds, offset + sdslen(value));
        cptr = ((struct Object *)o)->sds;
        cptr = sdsgrowzero(cptr, offset + sdslen(value));
        ((struct Object *)o)->sds = cptr;

        cp = ((struct Object *)o)->sds + offset;
        memcpy(cp, value, sdslen(value));

        signalModifiedKey(c, c->db, c->argv[1]);
        notifyKeyspaceEvent(NOTIFY_STRING, "setrange", c->argv[1], c->db);
        server++; // Approximation of server.setrange_commands++ based on assembly
    }

    addReplyLongLong(c, sdslen(((struct Object *)o)->sds));
}