void stbhw_free_tileset(stbhw_tileset *ts)
{
   int i;
   for (i=0; i < ts->num_keys; ++i)
      free(ts->keys[i]);
   for (i=0; i < ts->num_values; ++i)
      free(ts->values[i]);
   free(ts->keys);
   free(ts->values);
   ts->keys = NULL;
   ts->values = NULL;
   ts->num_keys = 0;
   ts->num_values = 0;
   ts->key_size = 0;
   ts->value_size = 0;
}