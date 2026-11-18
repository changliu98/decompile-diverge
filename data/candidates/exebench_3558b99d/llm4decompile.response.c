long ff_atomic_dec_long(ff_atomic_t *val)
{
    long ret;
    LOCK();
    ret = --val->l;
    UNLOCK();
    return ret;
}