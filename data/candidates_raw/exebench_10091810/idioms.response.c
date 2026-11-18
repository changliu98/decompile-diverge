void swap(struct card *a, struct card *b){
    int temp = a->value;
    a->value = b->value;
    b->value = temp;
    temp = a->suit;
    a->suit = b->suit;
    b->suit = temp;
    temp = a->rank;
    a->rank = b->rank;
    b->rank = temp;
}