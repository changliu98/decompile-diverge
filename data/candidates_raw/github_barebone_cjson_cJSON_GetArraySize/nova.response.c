int func0(struct Node *p) {
    struct Node *q = NULL;
    int counter = 0;
    if (p == NULL) {
        counter = 0;
    }

    else {
        q = p;
        while (q!= NULL) {
            counter++;
            q = q->next;
        }
    }
    return counter;
}