int
SM_init(SM_handle h)
{
    struct sm_struct *sm = (struct sm_struct *)h;

    sm->init_count = 10;
    return 0;
}