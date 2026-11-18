struct node *BGBBTJ_BC7_EncodeBlock_VecSwapB(struct node *first, struct node *second) {
    struct node *temp = first->next;
    first->next = second->next;
    second->next = temp;
    return first;
}