bool func0(int x, int y, int *map) {
    TileInfo *a = get_tile_info(x, map);
    TileInfo *b = get_tile_info(y, map);

    return get_collision(a->collision_type, b->collision_type, a->rotation,
                         b->rotation, map) &
           1;
}