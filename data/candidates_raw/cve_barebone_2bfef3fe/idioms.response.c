void cmd_setrange(struct client *c) {
    struct client *cl = c;
    char *val = cl->argv[3]->str;
    long offset;
    if (parse_offset(cl, cl->argv[2], &offset, 0)) return;
    if (offset < 0) {
        reply_error(cl, "offset is out of range");
        return;
    }
    struct robj *o = lookup_key(cl->db, cl->argv[1]);
    if (o == ((void *)0)) {
        if (strlen(val) == 0) {
            reply_null(cl, shared[0]);
            return;
        }
        struct client *cl = c;
        if (can_set(cl, offset + strlen(val), ((void *)0))) {
            struct robj *o = create_string(((void *)0), ((void *)0));
            set_key(cl->db, cl->argv[1], o);
        } else {
            struct client *cl = c;
            struct robj *o = create_string(((void *)0), ((void *)0));
            set_key(cl->db, cl->argv[1], o);
        }
    } else {
        if (can_set(cl, o, 0)) return;
        long osize = string_size(o);
        if (strlen(val) == 0) {
            reply_bulk(cl, osize);
            return;
        }
        if (can_set(cl, osize + offset + strlen(val), ((void *)0))) {
            struct client *cl = c;
            if (can_set(cl, offset + strlen(val), ((void *)0))) {
                struct robj *o = lookup_key(cl->db, cl->argv[1], o);
                if (strlen(val) == 0) {
                    reply_null(cl, ((void *)0));
                    return;
                }
                char *str = o->ptr;
                char *pos = str + offset;
                str = (char *)sdscatlen(str, strlen(val) + offset);
                o->ptr = str;
                pos = o->ptr + offset;
                str = (char *)sdscatlen(pos, val);
                o->ptr = str;
                update_key(cl, cl->db, cl->argv[1]);
                log_command(8, "setrange", cl->argv[1], cl->db->id);
                reply_bulk(cl, strlen(o->ptr));
                return;
            }
        }
        struct client *cl = c;
        if (can_set(cl, offset + strlen(val), ((void *)0))) {
            struct robj *o = lookup_key(cl->db, cl->argv[1], o);
            if (strlen(val) == 0) {
                reply_null(cl, ((void *)0));
                return;
            }
            char *str = o->ptr;
            char *pos = str + offset;
            str = (char *)sdscatlen(str, strlen(val) + offset);
            o->ptr = str;
            pos = o->ptr + offset;
            str = (char *)sdscatlen(pos, val);
            o->ptr = str;
            update_key(cl, cl->db, cl->argv[1]);
            log_command(8, "setrange", cl->argv[1], cl->db->id);
            reply_bulk(cl, strlen(o->ptr));
            return;
        }
    }
}