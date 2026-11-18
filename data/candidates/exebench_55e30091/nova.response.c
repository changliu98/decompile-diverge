struct node BGBBTJ_BC7_EncodeBlock_VecSwapA(struct node *a, struct node *b) {
    struct node temp = *a;
    *a = *b;
    *b = temp;
    return *a;
}