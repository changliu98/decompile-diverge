void gitn_box_del(GF_Box *s)
{
    unsigned short i;
    if (!s) return;
    for (i = 0; i < s->size; i++) {
        if (s->entries[i].data) {
            gf_free(s->entries[i].data);
        }
    }
    if (s->entries) {
        gf_free(s->entries);
    }
    gf_free(s);
}