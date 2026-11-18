int vis5d_color_table_set_alpha(vis5d_color_table_t *table, float alpha)
{
    table->Alpha = alpha;
    if (alpha < 0.0) {
       table->TransparentColor.r = 0.0;
       table->TransparentColor.g = 0.0;
       table->TransparentColor.b = 0.0;
       table->TransparentColor.a = 1.0;
       if (alpha == -2.0) {
          table->TransparentColor.r = 0.0;
          table->TransparentColor.g = 0.0;
          table->TransparentColor.b = 0.0;
          table->TransparentColor.a = 0.0;
       }
    }
    else {
       table->TransparentColor.r = alpha;
       table->TransparentColor.g = alpha;
       table->TransparentColor.b = alpha;
       table->TransparentColor.a = alpha;
    }
    return 0;
}