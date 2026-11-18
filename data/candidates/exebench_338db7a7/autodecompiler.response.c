void reduce_grid_address_double(int *node, int *max_node)
{
    int j;

    for(j = 0; j < 4; j++)
    {
        node[j] -= 2 * max_node[j] * (node[j] > max_node[j]);
    }
}