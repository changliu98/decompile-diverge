void stbhw_free_tileset(stbhw_tileset *tileset) {
  int i;
  for (i = 0; i < tileset->num_tiles; ++i) free(tileset->tiles[i]);
  for (i = 0; i < tileset->num_animations; ++i) free(tileset->animations[i]);
  free(tileset->tiles);
  free(tileset->animations);
  tileset->tiles = NULL;
  tileset->animations = NULL;
  tileset->tile_width = 0;
  tileset->num_tiles = 0;
  tileset->tile_height = 0;
  tileset->num_animations = 0;
}