static void fmtutil_macbitmap_read_pixmap_only_fields(lua_State *L, FILE *fp, struct file_md *md, const char *name) {
    do {
        lua_pushfstring(L, "md.%s", name);
        lua_gettable(L, 1);
        md->name = get_str(L, name + 0);
        md->date = get_str(L, name + 2);
        md->time = get_str(L, name + 4);
        md->cdate = get_str(L, name + 6);
        md->ctime = get_str(L, name + 8);
        md->mdate = get_str(L, name + 10);
        md->mtime = get_str(L, name + 12);
        lua_pushfstring(L, "md.%s.div", name);
        md->div = lua_tostring(L, -1);
        lua_pushfstring(L, "md.%s.unit", name);
        md->unit = lua_tostring(L, -1);
        lua_pushfstring(L, "md.%s.prec", name);
        md->prec = lua_tointeger(L, -1);
        lua_pop(L, -1);
    } while (md->prec < md->unit);
    md->unit = md->unit / md->div;
}