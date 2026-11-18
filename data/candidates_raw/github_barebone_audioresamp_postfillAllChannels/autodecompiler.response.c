void
xvm_free(xvm_t *xvm)
{
 free__bench(xvm->stack);
 free__bench(xvm->mem);
 free__bench(xvm->code);
 free__bench(xvm->frame);
}