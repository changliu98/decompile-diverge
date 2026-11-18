void gitn_box_del(struct gitn_box *box) {
    if (box == NULL) {
        return;
    }

    for (unsigned int i = 0; i < box->field_0x28; i++) {
        if (box->items[i].ptr != NULL) {
            gf_free(box->items[i].ptr);
        }
    }

    if (box->items != NULL) {
        gf_free(box->items);
    }

    gf_free(box);
}