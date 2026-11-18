struct node *func0(struct node *first, struct node *second) {
    struct node *temp = first->next;
    first->next = second->next;
    second->next = temp;
    return first;
}