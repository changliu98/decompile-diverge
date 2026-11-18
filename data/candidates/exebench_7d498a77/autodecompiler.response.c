int get_priority(int type, id_t rid, struct rlimit *lim)
{
 lim->rlim_cur = getpriority(0, (int)rid);
 return *___errno_location();
}