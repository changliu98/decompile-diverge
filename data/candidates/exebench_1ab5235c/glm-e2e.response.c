void BGBBTJ_BC7_EncodeBlock_VecSwapB(struct Block *a, struct Block *b) {
    int temp = a->val;
    a->val = b->val;
    b->val = temp;
}