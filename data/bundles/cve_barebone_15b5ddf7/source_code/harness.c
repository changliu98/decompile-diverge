/* cve_barebone direct-call harness for CVE-2018-20541 (libxsmm)
 * Target: libxsmm_sparse_csc_reader  (src/generator_spgemm_csc_reader.c)
 * Bug class: heap-based buffer overflow, CWE-787 (confirmed by NVD: "There is a
 *   heap-based buffer overflow in libxsmm_sparse_csc_reader at
 *   generator_spgemm_csc_reader.c in LIBXSMM 1.10").
 *
 * Root cause: while reading the per-nonzero data lines of a "CSC matrix-market"
 * style text file ("row col value", 1-based), the function decrements the
 * user-supplied column index (`l_column = <file column> - 1`) and then writes
 * through it WITHOUT ever checking `l_column < *o_column_count`:
 *     l_column_idx_id[l_column] = 1;
 *     (*o_column_idx)[l_column+1] = l_i;
 * `l_column_idx_id` and `*o_column_idx` were malloc'd sized by the DECLARED
 * `*o_column_count` from the file's own header line -- so a data line whose
 * column field exceeds the declared column count overflows both heap buffers.
 * The official fix (commit 151481489192e6d1997f8bde52c5c425ea41741d) only adds
 * a `!= 0` guard on the header fields and an assert that row/col aren't 0; it
 * does NOT add a `l_column < *o_column_count` bound, so this overflow is the
 * (unfixed-by-that-patch, but CVE-confirmed) heap-buffer-overflow bug.
 *
 * The vulnerable function only depends on primitive libc types plus two
 * project macros (LIBXSMM_API_INTERN, LIBXSMM_HANDLE_ERROR) and one opaque
 * struct pointer type (libxsmm_generated_code*) that the function never
 * dereferences -- so a minimal opaque typedef + no-op macro stand-ins are the
 * faithful minimal stand-ins (libxsmm itself ships a LIBXSMM_HANDLE_ERROR_QUIET
 * configuration that expands LIBXSMM_HANDLE_ERROR to nothing, so the no-op here
 * matches a real supported configuration).
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Faithful minimal stand-ins for the project macros/types the function's
 * signature and body reference. LIBXSMM_HANDLE_ERROR is a no-op here, matching
 * libxsmm's own LIBXSMM_HANDLE_ERROR_QUIET build configuration. noinline keeps
 * the target function as its own stack frame under ASAN (it is otherwise the
 * sole call site in this TU and clang would fold it into main at -O1). */
#define LIBXSMM_API_INTERN __attribute__((noinline))
#define LIBXSMM_HANDLE_ERROR(GENERATED_CODE, ERROR_CODE) ((void)0)
typedef struct libxsmm_generated_code libxsmm_generated_code; /* opaque; never dereferenced */

/* ==== VERBATIM from data_cve/cve_15b5ddf7/target/original_function.c ==== */
LIBXSMM_API_INTERN
void libxsmm_sparse_csc_reader( libxsmm_generated_code* io_generated_code,
                                const char*             i_csc_file_in,
                                unsigned int**          o_row_idx,
                                unsigned int**          o_column_idx,
                                double**                o_values,
                                unsigned int*           o_row_count,
                                unsigned int*           o_column_count,
                                unsigned int*           o_element_count ) {
  FILE *l_csc_file_handle;
  const unsigned int l_line_length = 512;
  char l_line[512/*l_line_length*/+1];
  unsigned int l_header_read = 0;
  unsigned int* l_column_idx_id = NULL;
  unsigned int l_i = 0;

  l_csc_file_handle = fopen( i_csc_file_in, "r" );
  if ( l_csc_file_handle == NULL ) {
    LIBXSMM_HANDLE_ERROR( io_generated_code, LIBXSMM_ERR_CSC_INPUT );
    return;
  }

  while (fgets(l_line, l_line_length, l_csc_file_handle) != NULL) {
    if ( strlen(l_line) == l_line_length ) {
      free(*o_row_idx); free(*o_column_idx); free(*o_values); free(l_column_idx_id);
      *o_row_idx = 0; *o_column_idx = 0; *o_values = 0;
      fclose( l_csc_file_handle ); /* close mtx file */
      LIBXSMM_HANDLE_ERROR( io_generated_code, LIBXSMM_ERR_CSC_READ_LEN );
      return;
    }
    /* check if we are still reading comments header */
    if ( l_line[0] == '%' ) {
      continue;
    } else {
      /* if we are the first line after comment header, we allocate our data structures */
      if ( l_header_read == 0 ) {
        if ( sscanf(l_line, "%u %u %u", o_row_count, o_column_count, o_element_count) == 3 ) {
          /* allocate CSC data structure matching mtx file */
          *o_row_idx = (unsigned int*) malloc(sizeof(unsigned int) * (*o_element_count));
          *o_column_idx = (unsigned int*) malloc(sizeof(unsigned int) * ((size_t)(*o_column_count) + 1));
          *o_values = (double*) malloc(sizeof(double) * (*o_element_count));
          l_column_idx_id = (unsigned int*) malloc(sizeof(unsigned int) * (*o_column_count));

          /* check if mallocs were successful */
          if ( ( *o_row_idx == NULL )      ||
               ( *o_column_idx == NULL )   ||
               ( *o_values == NULL )       ||
               ( l_column_idx_id == NULL ) ) {
            free(*o_row_idx); free(*o_column_idx); free(*o_values); free(l_column_idx_id);
            *o_row_idx = 0; *o_column_idx = 0; *o_values = 0;
            fclose(l_csc_file_handle); /* close mtx file */
            LIBXSMM_HANDLE_ERROR( io_generated_code, LIBXSMM_ERR_CSC_ALLOC_DATA );
            return;
          }

          /* set everything to zero for init */
          memset(*o_row_idx, 0, sizeof(unsigned int) * (*o_element_count));
          memset(*o_column_idx, 0, sizeof(unsigned int) * ((size_t)(*o_column_count) + 1));
          memset(*o_values, 0, sizeof(double) * (*o_element_count));
          memset(l_column_idx_id, 0, sizeof(unsigned int) * (*o_column_count));

          /* init column idx */
          for (l_i = 0; l_i <= *o_column_count; ++l_i) {
            (*o_column_idx)[l_i] = *o_element_count;
          }
          /* init */
          (*o_column_idx)[0] = 0;
          l_i = 0;
          l_header_read = 1;
        } else {
          LIBXSMM_HANDLE_ERROR( io_generated_code, LIBXSMM_ERR_CSC_READ_DESC );
          fclose( l_csc_file_handle ); /* close mtx file */
          return;
        }
      /* now we read the actual content */
      } else {
        unsigned int l_row = 0, l_column = 0;
        double l_value = 0;
        /* read a line of content */
        if ( sscanf(l_line, "%u %u %lf", &l_row, &l_column, &l_value) != 3 ) {
          free(*o_row_idx); free(*o_column_idx); free(*o_values); free(l_column_idx_id);
          *o_row_idx = 0; *o_column_idx = 0; *o_values = 0;
          fclose(l_csc_file_handle); /* close mtx file */
          LIBXSMM_HANDLE_ERROR( io_generated_code, LIBXSMM_ERR_CSC_READ_ELEMS );
          return;
        }
        /* adjust numbers to zero termination */
        l_row--;
        l_column--;
        /* add these values to row and value structure */
        (*o_row_idx)[l_i] = l_row;
        (*o_values)[l_i] = l_value;
        l_i++;
        /* handle columns, set id to own for this column, yeah we need to handle empty columns */
        l_column_idx_id[l_column] = 1;
        (*o_column_idx)[l_column+1] = l_i;
      }
    }
  }

  /* close mtx file */
  fclose( l_csc_file_handle );

  /* check if we read a file which was consistent */
  if ( l_i != (*o_element_count) ) {
    free(*o_row_idx); free(*o_column_idx); free(*o_values); free(l_column_idx_id);
    *o_row_idx = 0; *o_column_idx = 0; *o_values = 0;
    LIBXSMM_HANDLE_ERROR( io_generated_code, LIBXSMM_ERR_CSC_LEN );
    return;
  }

  if ( l_column_idx_id != NULL ) {
    /* let's handle empty columns */
    for ( l_i = 0; l_i < (*o_column_count); l_i++) {
      if ( l_column_idx_id[l_i] == 0 ) {
        (*o_column_idx)[l_i+1] = (*o_column_idx)[l_i];
      }
    }

    /* free helper data structure */
    free( l_column_idx_id );
  }
}
/* ==== end verbatim ==== */

int main(int argc, char** argv)
{
  if (argc < 2)
    return 0;

  /* HEAP-allocate the input FILE PATH's contents is not what's read here --
   * the function itself takes a *file path* (fopen'd inside), so instead we
   * copy argv[1] (the harness's own input file) into a heap buffer holding
   * the PATH string, matching the "read argv[1] as a file" contract: the
   * fuzzed file's bytes ARE the CSC-format text the function fopen()s and
   * parses directly, so we simply pass the path through. No intermediate
   * heap copy of the CONTENT is needed since the function does its own I/O
   * on the path we hand it -- but we still heap-allocate the path string
   * itself so ASAN guards it like every other harness in this axis. */
  size_t plen = strlen(argv[1]);
  char* path = (char*)malloc(plen + 1);
  if (!path) return 0;
  memcpy(path, argv[1], plen + 1);

  unsigned int* row_idx = NULL;
  unsigned int* column_idx = NULL;
  double* values = NULL;
  unsigned int row_count = 0, column_count = 0, element_count = 0;

  libxsmm_sparse_csc_reader(NULL, path, &row_idx, &column_idx, &values,
                             &row_count, &column_count, &element_count);

  fprintf(stderr, "ok rows=%u cols=%u elems=%u\n", row_count, column_count, element_count);

  free(row_idx);
  free(column_idx);
  free(values);
  free(path);
  return 0;
}
