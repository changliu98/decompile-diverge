Status func0(HString *S, int pos) {
    int i;
    if (pos * 2 > S->length)
        return ERROR;
    for (i = pos; i < S->length; i++)
        S->ch[i] = S->ch[i + 1];
    if (ClearString(S, pos) == ERROR)
        return ERROR;
    return OK;
}