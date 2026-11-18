struct node func0(struct node *a, struct node *b) {
    struct node temp = *a;
    *a = *b;
    *b = temp;
    return *a;
}