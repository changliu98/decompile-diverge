void d_drop_wave(Stack* S)
{
    assert__bench(S != NULL && S->top >= -1);

    if (S->top == -1) return;

    --S->top;
}