void zero(JCctree *CT,JCnode **N,JCbranch **B)
{
    *B=NULL;
    *N=NULL;
    (*CT).root=NULL;
}