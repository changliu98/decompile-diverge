void mcid_char_imp(ctx_t *ctx, void *unused, node_t *node, int a, int b) {
    if (node->dict == NULL) {
        return;
    }

    if (b != 0) {
        pdf_dict_del(ctx, node->dict, 1);
        pdf_dict_del(ctx, node->dict, 2);
    }

    walk_string(ctx, a, b, node->str1);
    walk_string(ctx, a, b, node->str2);

    if (b != 0) {
        b = (node->val1 == -1 || node->val2 == -1);
    } else {
        if (node->val1 >= 0 || node->val2 >= 0) {
            b = 0;
        }
    }

    if (b == 0) {
        return;
    }

    if (node->val2 == -1) {
        pdf_dict_del(ctx, node->dict, 3);
    }
    if (node->val1 == -1) {
        pdf_dict_del(ctx, node->dict, 4);
    }

    pdf_drop_obj(ctx, node->dict);
    node->dict = NULL;

    fz_free(ctx, node->str1);
    node->str1 = NULL;

    fz_free(ctx, node->str2);
    node->str2 = NULL;
}