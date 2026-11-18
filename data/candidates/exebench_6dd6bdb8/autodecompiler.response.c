void get_grid_address_from_index( struct grid_coord *gc, long long int hash, struct grid *D )
{
 long long int n = D->N * D->M;
 gc->x = hash % D->N;
 gc->y = hash / n;
 gc->z = (hash - gc->y * n) / D->N;
}