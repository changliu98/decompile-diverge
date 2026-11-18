Status func0(LinkList *L, int i, LinkListPtr *p) {
    LinkListPtr s;
    Status k = TRUE;

    if (i < 1 || p == NULL) {
        k = FALSE;
    } else {
        s = GetElem(*L, i);
        if (s == NULL) {
            k = func0_S(L, p);
        } else {
            if (s == (*L)->next || s->next == NULL) {
                k = FALSE;
            } else {
                *p = s;
                (*p)->next = s->next;
                s->next->prior = *p;
                if (s == (*L)->prior) {
                    (*L)->prior = *p;
                } else {
                    (*p)->prior = s->prior;
                }
                k = TRUE;
            }
        }
    }

    return k;
}