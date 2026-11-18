void stb_boxplot_center(stb_boxplot *bp)
{
   int i,j,k;
   int **ranks;
   int **count;
   int *offset;
   double *mean;
   stb_matrix *m=NULL;
   stb_transpose_matrix(bp, &m);
   ranks = (int **) malloc(sizeof(*ranks) * bp->w);
   count = (int **) malloc(sizeof(*count) * bp->w);
   offset = (int *) malloc(sizeof(*offset) * bp->w);

   for (i=0; i < m->w; ++i) {
      stb_didx(m->m[i], offset+i, ranks+i, count+i, m->h);
   }

   mean = (double *) malloc(sizeof(*mean) * bp->h);
   {
      stb_matrix *t=NULL;
      stb_transpose_matrix(m, &t);
      _D2rt5tlsgc7destroyFNbNiPvZv(m);
      for (i=0; i < t->w; ++i) {
         double dummy;
         stb_meanvar(t->m[i], t->h, mean+i, &dummy);
      }
      _D2rt5tlsgc7destroyFNbNiPvZv(t);
   }

   for (i=0; i < bp->w; ++i) {
      for (j=0; j < bp->h; ++j) {
         bp->m[offset[i]+j][i] = 0;
         for (k=0; k < count[i][ranks[i][j]]; ++k)
            bp->m[offset[i]+j][i] += mean[ranks[i][j]+k];
         bp->m[offset[i]+j][i] /= count[i][ranks[i][j]];
      }
   }

   for (i=0; i < bp->w; ++i) {
      free(offset[i]);
      free(ranks[i]);
      free(count[i]);
   }
   free(offset);
   free(ranks);
   free(count);
   free(mean);
}