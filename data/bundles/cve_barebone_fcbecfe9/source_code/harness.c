/* cve_barebone direct-call harness for CVE-2025-13397 (mrubyc, mrbc_raw_realloc)
 * Target: mrbc_raw_realloc (src/alloc.c) -- CWE-476 wild-pointer dereference (SEGV).
 *
 * Fix (009111904807b8567262036bf45297c3da8f1c87):
 *   -  if (ptr != NULL && size == 0) {
 *   -    mrbc_raw_free(ptr);
 *   +  if( ptr == NULL ) {
 *   +    return mrbc_raw_alloc(size);
 *   +  }
 *   +  if( size == 0 ) {
 *   +    mrbc_raw_free(ptr);              // C90(glibc) compatible.
 *        return NULL;
 *      }
 *
 * The pre-fix mrbc_raw_realloc() only special-cases "ptr!=NULL && size==0" (free-and-
 * return-NULL). It has NO check at all for "ptr==NULL" -- the realloc(NULL,size)==
 * malloc(size) convention every C allocator is expected to honour, which the fix restores
 * via `mrbc_raw_alloc(size)`. So mrbc_raw_realloc(NULL, size) (any size, including 0) falls
 * straight through to:
 *     volatile USED_BLOCK *target = BLOCK_ADRS(ptr);   // = NULL - sizeof(USED_BLOCK)
 *     ...
 *     if( alloc_size > BLOCK_SIZE(target) ) {          // dereferences target->size
 * BLOCK_ADRS(NULL) computes a wild pointer a few bytes below address 0 (wraps to a huge,
 * unmapped address in a 64-bit process); BLOCK_SIZE(target) then reads target->size
 * through it -- a read via a wild/near-null pointer -> SIGSEGV, caught by ASAN as "SEGV on
 * unknown address" inside mrbc_raw_realloc itself.
 *
 * Every mruby/c type/macro/helper function used below (USED_BLOCK/FREE_BLOCK/MEMORY_POOL
 * layout, BLOCK_ADRS/BLOCK_SIZE/PHYS_NEXT/... macros, nlz16/nlz8/calc_index/
 * add_free_block/remove_free_block/split_block/merge_block/mrbc_init_alloc/
 * mrbc_raw_alloc/mrbc_raw_free/mrbc_set_vm_id, and hal_write) is copied VERBATIM (exact
 * line slices) from src/alloc.c / src/alloc.h / hal/posix/hal.h in the vulnerable tree,
 * built with the SAME feature flags the file's own #if/#elif ladder requires:
 * MRBC_ALLOC_24BIT (vm_config.h's only choice besides the 16-bit variant) and
 * MRBC_ALLOC_VMID -- the latter is REQUIRED, not merely a faithful default: the target
 * function's own body unconditionally reads `target->vm_id`
 * (`mrbc_set_vm_id(new_ptr, target->vm_id);` in the ALLOC_AND_COPY branch), a struct
 * member that exists ONLY in the `#if defined(MRBC_ALLOC_VMID)` branch of the USED_BLOCK
 * typedef -- so this exact revision cannot even compile without it. MRBC_DEBUG /
 * MRBC_USE_ALLOC_PROF are left undefined (a real, supported release-mode configuration --
 * vm_config.h's own `#define MRBC_DEBUG` is itself conditioned on `!defined(NDEBUG)`);
 * nothing MRBC_DEBUG guards sits on mrbc_raw_realloc's own path, only extra diagnostics in
 * the allocator helpers it calls.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

#define NDEBUG          /* real release-mode config: MRBC_DEBUG is `!defined(NDEBUG)` in
                          * vm_config.h; disables the assert()s the pasted allocator
                          * internals use below (none sit on mrbc_raw_realloc's own path). */
#include <assert.h>

/* ---- feature flags: the ONLY combination src/alloc.c's own #if/#elif ladder allows that
 * lets this exact revision compile (see header comment -- MRBC_ALLOC_VMID is REQUIRED). */
#define MRBC_ALLOC_24BIT
#define MRBC_ALLOC_VMID

/* ---- hal_write: VERBATIM (hal/posix/hal.h) -- the real POSIX HAL backend. Referenced
 * unconditionally (NOT MRBC_DEBUG-gated) by mrbc_raw_alloc's out-of-memory branch below,
 * so it must be a real symbol for the link to succeed, even though our pool is sized to
 * never actually hit it. */
inline static int hal_write(int fd, const void *buf, int nbytes)
{
  return (int)write(1, buf, nbytes);
}

/* ================= verbatim, src/alloc.c 79-430 (macros/typedefs/pool layout/helpers) === */
#ifndef MRBC_ALLOC_FLI_BIT_WIDTH	// 0000 0000 0000 0000
# define MRBC_ALLOC_FLI_BIT_WIDTH 9	// ~~~~~~~~~~~
#endif
#ifndef MRBC_ALLOC_SLI_BIT_WIDTH	// 0000 0000 0000 0000
# define MRBC_ALLOC_SLI_BIT_WIDTH 3	//            ~~~
#endif
#ifndef MRBC_ALLOC_IGNORE_LSBS		// 0000 0000 0000 0000
# define MRBC_ALLOC_IGNORE_LSBS	  4	//                ~~~~
#endif

#define SIZE_FREE_BLOCKS \
  ((MRBC_ALLOC_FLI_BIT_WIDTH + 1) * (1 << MRBC_ALLOC_SLI_BIT_WIDTH))
					// maybe 80 (0x50)
/*
   Minimum memory block size parameter.
   Choose large one from sizeof(FREE_BLOCK) or (1 << MRBC_ALLOC_IGNORE_LSBS)
*/
#if !defined(MRBC_MIN_MEMORY_BLOCK_SIZE)
#define MRBC_MIN_MEMORY_BLOCK_SIZE sizeof(FREE_BLOCK)
// #define MRBC_MIN_MEMORY_BLOCK_SIZE (1 << MRBC_ALLOC_IGNORE_LSBS)
#endif


/***** Macros ***************************************************************/
#define FLI(x) ((x) >> MRBC_ALLOC_SLI_BIT_WIDTH)
#define SLI(x) ((x) & ((1 << MRBC_ALLOC_SLI_BIT_WIDTH) - 1))


/***** Typedefs *************************************************************/
/*
  define memory block header for 16 bit

  (note)
  Typical size of
    USED_BLOCK is 2 bytes
    FREE_BLOCK is 8 bytes
  on 16bit machine.
*/
#if defined(MRBC_ALLOC_16BIT)
#define MRBC_ALLOC_MEMSIZE_T	uint16_t

typedef struct USED_BLOCK {
  MRBC_ALLOC_MEMSIZE_T size;		//!< block size, header included
#if defined(MRBC_ALLOC_VMID)
  uint8_t	       vm_id;		//!< mruby/c VM ID
#endif
} USED_BLOCK;

typedef struct FREE_BLOCK {
  MRBC_ALLOC_MEMSIZE_T size;		//!< block size, header included
#if defined(MRBC_ALLOC_VMID)
  uint8_t	       vm_id;		//!< dummy
#endif

  struct FREE_BLOCK *next_free;
  struct FREE_BLOCK *prev_free;
  struct FREE_BLOCK *top_adrs;		//!< dummy for calculate sizeof(FREE_BLOCK)
} FREE_BLOCK;


/*
  define memory block header for 24/32 bit.

  (note)
  Typical size of
    USED_BLOCK is  4 bytes
    FREE_BLOCK is 16 bytes
  on 32bit machine.
*/
#elif defined(MRBC_ALLOC_24BIT)
#define MRBC_ALLOC_MEMSIZE_T	uint32_t

typedef struct USED_BLOCK {
#if defined(MRBC_ALLOC_VMID)
  MRBC_ALLOC_MEMSIZE_T size : 24;	//!< block size, header included
  uint8_t	       vm_id : 8;	//!< mruby/c VM ID
#else
  MRBC_ALLOC_MEMSIZE_T size;
#endif
} USED_BLOCK;

typedef struct FREE_BLOCK {
#if defined(MRBC_ALLOC_VMID)
  MRBC_ALLOC_MEMSIZE_T size : 24;	//!< block size, header included
  uint8_t	       vm_id : 8;	//!< dummy
#else
  MRBC_ALLOC_MEMSIZE_T size;
#endif

  struct FREE_BLOCK *next_free;
  struct FREE_BLOCK *prev_free;
  struct FREE_BLOCK *top_adrs;		//!< dummy for calculate sizeof(FREE_BLOCK)
} FREE_BLOCK;

#else
# error 'define MRBC_ALLOC_*' required.
#endif

/*
  and operation macro
*/
#define BLOCK_SIZE(p)		(((p)->size) & ~0x03)
#define PHYS_NEXT(p)		((void *)((uint8_t *)(p) + BLOCK_SIZE(p)))
#define SET_USED_BLOCK(p)	((p)->size |=  0x01)
#define SET_FREE_BLOCK(p)	((p)->size &= ~0x01)
#define IS_USED_BLOCK(p)	((p)->size &   0x01)
#define IS_FREE_BLOCK(p)	(!IS_USED_BLOCK(p))
#define SET_PREV_USED(p)	((p)->size |=  0x02)
#define SET_PREV_FREE(p)	((p)->size &= ~0x02)
#define IS_PREV_USED(p)		((p)->size &   0x02)
#define IS_PREV_FREE(p)		(!IS_PREV_USED(p))

#if defined(MRBC_ALLOC_VMID)
#define SET_VM_ID(p,id)	(((USED_BLOCK *)(p))->vm_id = (id))
#define GET_VM_ID(p)	(((USED_BLOCK *)(p))->vm_id)

#else
#define SET_VM_ID(p,id)	((void)0)
#define GET_VM_ID(p)	0
#endif


/*
  define memory pool header
*/
typedef struct MEMORY_POOL {
  MRBC_ALLOC_MEMSIZE_T size;

  // free memory bitmap
  uint16_t free_fli_bitmap;
  uint8_t  free_sli_bitmap[MRBC_ALLOC_FLI_BIT_WIDTH +1+1];
						// +1=bit_width, +1=sentinel
  uint8_t  pad[3]; // for alignment compatibility on 16bit and 32bit machines

  // free memory block index
  FREE_BLOCK *free_blocks[SIZE_FREE_BLOCKS +1];	// +1=sentinel
} MEMORY_POOL;

#define BPOOL_TOP(memory_pool) ((void *)((uint8_t *)(memory_pool) + sizeof(MEMORY_POOL)))
#define BPOOL_END(memory_pool) ((void *)((uint8_t *)(memory_pool) + ((MEMORY_POOL *)(memory_pool))->size))
#define BLOCK_ADRS(p) ((void *)((uint8_t *)(p) - sizeof(USED_BLOCK)))

#define MSB_BIT1_FLI 0x8000
#define MSB_BIT1_SLI 0x80
#define NLZ_FLI(x) nlz16(x)
#define NLZ_SLI(x) nlz8(x)


/***** Function prototypes **************************************************/
/***** Local variables ******************************************************/
// memory pool
static MEMORY_POOL *memory_pool;

#if defined(MRBC_USE_ALLOC_PROF)
static int profiling = 0;
static struct MRBC_ALLOC_PROF alloc_prof = {0, 0, 0};
#endif

/***** Global variables *****************************************************/
/***** Signal catching functions ********************************************/
/***** Local functions ******************************************************/
//================================================================
/*! Number of leading zeros. 16bit version.

  @param  x	target (16bit unsigned)
  @retval int	nlz value
*/
static inline int nlz16(uint16_t x)
{
  if( x == 0 ) return 16;

  int n = 1;
  if((x >>  8) == 0 ) { n += 8; x <<= 8; }
  if((x >> 12) == 0 ) { n += 4; x <<= 4; }
  if((x >> 14) == 0 ) { n += 2; x <<= 2; }
  return n - (x >> 15);
}


//================================================================
/*! Number of leading zeros. 8bit version.

  @param  x	target (8bit unsigned)
  @retval int	nlz value
*/
static inline int nlz8(uint8_t x)
{
  if( x == 0 ) return 8;

  int n = 1;
  if((x >> 4) == 0 ) { n += 4; x <<= 4; }
  if((x >> 6) == 0 ) { n += 2; x <<= 2; }
  return n - (x >> 7);
}


//================================================================
/*! calc f and s, and returns fli,sli of free_blocks

  @param  alloc_size	alloc size
  @retval unsigned int	index of free_blocks
*/
static inline unsigned int calc_index(MRBC_ALLOC_MEMSIZE_T alloc_size)
{
  // check overflow
  if( (alloc_size >> (MRBC_ALLOC_FLI_BIT_WIDTH
                      + MRBC_ALLOC_SLI_BIT_WIDTH
                      + MRBC_ALLOC_IGNORE_LSBS)) != 0) {
    return SIZE_FREE_BLOCKS - 1;
  }

  // calculate First Level Index.
  unsigned int fli = 16 -
    nlz16( alloc_size >> (MRBC_ALLOC_SLI_BIT_WIDTH + MRBC_ALLOC_IGNORE_LSBS) );

  // calculate Second Level Index.
  unsigned int shift = (fli == 0) ? MRBC_ALLOC_IGNORE_LSBS :
                                   (MRBC_ALLOC_IGNORE_LSBS - 1 + fli);

  unsigned int sli = (alloc_size >> shift) & ((1 << MRBC_ALLOC_SLI_BIT_WIDTH) - 1);
  unsigned int index = (fli << MRBC_ALLOC_SLI_BIT_WIDTH) + sli;

  assert(fli <= MRBC_ALLOC_FLI_BIT_WIDTH);
  assert(sli <= (1 << MRBC_ALLOC_SLI_BIT_WIDTH) - 1);

  return index;
}


//================================================================
/*! Mark that block free and register it in the free index table.

  @param  pool		Pointer to memory pool.
  @param  target	Pointer to target block.
*/
static void add_free_block(MEMORY_POOL *pool, FREE_BLOCK *target)
{
  SET_FREE_BLOCK(target);

  FREE_BLOCK **top_adrs = (FREE_BLOCK **)((uint8_t*)target + BLOCK_SIZE(target) - sizeof(FREE_BLOCK *));
  *top_adrs = target;

  unsigned int index = calc_index(BLOCK_SIZE(target));
  unsigned int fli = FLI(index);
  unsigned int sli = SLI(index);
  assert( index < SIZE_FREE_BLOCKS );

  pool->free_fli_bitmap      |= (MSB_BIT1_FLI >> fli);
  pool->free_sli_bitmap[fli] |= (MSB_BIT1_SLI >> sli);

  target->prev_free = NULL;
  target->next_free = pool->free_blocks[index];
  if( target->next_free != NULL ) {
    target->next_free->prev_free = target;
  }
  pool->free_blocks[index] = target;
}


//================================================================
/*! just remove the free_block *target from index

  @param  pool		Pointer to memory pool.
  @param  target	pointer to target block.
*/
static void remove_free_block(MEMORY_POOL *pool, FREE_BLOCK *target)
{
  // top of linked list?
  if( target->prev_free == NULL ) {
    unsigned int index = calc_index(BLOCK_SIZE(target));

    pool->free_blocks[index] = target->next_free;
    if( target->next_free == NULL ) {
      unsigned int fli = FLI(index);
      unsigned int sli = SLI(index);
      pool->free_sli_bitmap[fli] &= ~(MSB_BIT1_SLI >> sli);
      if( pool->free_sli_bitmap[fli] == 0 ) pool->free_fli_bitmap &= ~(MSB_BIT1_FLI >> fli);
    }
  }
  else {
    target->prev_free->next_free = target->next_free;
  }

  if( target->next_free != NULL ) {
    target->next_free->prev_free = target->prev_free;
  }
}


#if defined(MRBC_USE_ALLOC_PROF)
//================================================================
/*! Record current memory usage for profiling
*/
static void alloc_profile(void)
{
  if (!profiling) return;

  MEMORY_POOL *pool = memory_pool;
  USED_BLOCK *block = BPOOL_TOP(pool);
  unsigned int used = 0;

  while (block < (USED_BLOCK *)BPOOL_END(pool)) {
    if (!IS_FREE_BLOCK(block)) {
      used += BLOCK_SIZE(block);
    }
    block = PHYS_NEXT(block);
  }

  if (alloc_prof.max < used) alloc_prof.max = used;
  if (used < alloc_prof.min) alloc_prof.min = used;
}
#else
#define alloc_profile() ((void)0)
#endif

//================================================================
/*! Split block by size

  @param  target	pointer to target block
  @param  size		size
  @retval NULL		no split.
  @retval FREE_BLOCK *	pointer to splitted free block.
*/
static inline FREE_BLOCK* split_block(FREE_BLOCK *target, MRBC_ALLOC_MEMSIZE_T size)
{
  assert( BLOCK_SIZE(target) >= size );
  if( (BLOCK_SIZE(target) - size) <= MRBC_MIN_MEMORY_BLOCK_SIZE ) return NULL;

  // split block, free
  FREE_BLOCK *split = (FREE_BLOCK *)((uint8_t *)target + size);

  split->size  = BLOCK_SIZE(target) - size;
  target->size = size | (target->size & 0x03);	// copy a size with flags.

  return split;
}


//================================================================
/*! merge target and next block.
    next will disappear

  @param  target	pointer to free block 1
  @param  next	pointer to free block 2
*/
static inline void merge_block(FREE_BLOCK *target, FREE_BLOCK *next)
{
  assert(target < next);

  // merge target and next
  target->size += BLOCK_SIZE(next);		// copy a size but save flags.
}

/* ================= verbatim, src/alloc.c 433-477 (mrbc_init_alloc) ====================== */
/***** Global functions *****************************************************/
//================================================================
/*! initialize

  @param  ptr	pointer to free memory block.
  @param  size	size. (max 64KB. see MRBC_ALLOC_MEMSIZE_T)
*/
void mrbc_init_alloc(void *ptr, unsigned int size)
{
  assert( MRBC_MIN_MEMORY_BLOCK_SIZE >= sizeof(FREE_BLOCK) );
  assert( MRBC_MIN_MEMORY_BLOCK_SIZE >= (1 << MRBC_ALLOC_IGNORE_LSBS) );
  /*
    If you get this assertion, you can change minimum memory block size
    parameter to `MRBC_MIN_MEMORY_BLOCK_SIZE (1 << MRBC_ALLOC_IGNORE_LSBS)`
    and #define MRBC_ALLOC_16BIT.
  */

  assert( (sizeof(MEMORY_POOL) & 0x03) == 0 );
#if defined(UINTPTR_MAX)
  assert( ((uintptr_t)ptr & 0x03) == 0 );
#else
  assert( ((uint32_t)ptr & 0x03) == 0 );
#endif
  assert( size != 0 );
  assert( size <= (MRBC_ALLOC_MEMSIZE_T)(~0) );

  size &= ~(unsigned int)0x03;	// align 4 byte.
  memory_pool = ptr;
  memset( memory_pool, 0, sizeof(MEMORY_POOL) );
  memory_pool->size = size;

  // initialize memory pool
  //  large free block + zero size used block (sentinel).
  MRBC_ALLOC_MEMSIZE_T sentinel_size = sizeof(USED_BLOCK);
  sentinel_size += (-sentinel_size & 0x03);
  MRBC_ALLOC_MEMSIZE_T free_size = size - sizeof(MEMORY_POOL) - sentinel_size;
  FREE_BLOCK *free_block = BPOOL_TOP(memory_pool);
  USED_BLOCK *used_block = (USED_BLOCK *)((uint8_t *)free_block + free_size);

  free_block->size = free_size | 0x02;		// flag prev=1, used=0
  used_block->size = sentinel_size | 0x01;	// flag prev=0, used=1
  SET_VM_ID( used_block, 0xff );

  add_free_block( memory_pool, free_block );
}

/* ================= verbatim, src/alloc.c 495-608 (mrbc_raw_alloc) ======================= */
//================================================================
/*! allocate memory

  @param  size	request size.
  @return void * pointer to allocated memory.
  @retval NULL	error.
*/
void * mrbc_raw_alloc(unsigned int size)
{
  MEMORY_POOL *pool = memory_pool;
  MRBC_ALLOC_MEMSIZE_T alloc_size = size + sizeof(USED_BLOCK);

  // align 4 byte
  alloc_size += (-alloc_size & 3);

  // check minimum alloc size.
  if( alloc_size < MRBC_MIN_MEMORY_BLOCK_SIZE ) alloc_size = MRBC_MIN_MEMORY_BLOCK_SIZE;

  FREE_BLOCK *target;
  unsigned int fli, sli;
  unsigned int index = calc_index(alloc_size);

  // At first, check only the beginning of the same size block.
  // because it immediately responds to the pattern in which
  // same size memory are allocated and released continuously.
  target = pool->free_blocks[index];
  if( target && BLOCK_SIZE(target) >= alloc_size ) {
    fli = FLI(index);
    sli = SLI(index);
    goto FOUND_TARGET_BLOCK;
  }

  // and then, check the next (larger) size block.
  target = pool->free_blocks[++index];
  fli = FLI(index);
  sli = SLI(index);
  if( target ) goto FOUND_TARGET_BLOCK;

  // check in SLI bitmap table.
  uint16_t masked = pool->free_sli_bitmap[fli] & ((MSB_BIT1_SLI >> sli) - 1);
  if( masked != 0 ) {
    sli = NLZ_SLI( masked );
    goto FOUND_FLI_SLI;
  }

  // check in FLI bitmap table.
  masked = pool->free_fli_bitmap & ((MSB_BIT1_FLI >> fli) - 1);
  if( masked != 0 ) {
    fli = NLZ_FLI( masked );
    sli = NLZ_SLI( pool->free_sli_bitmap[fli] );
    goto FOUND_FLI_SLI;
  }

  // Change strategy to First-fit.
  target = pool->free_blocks[--index];
  while( target ) {
    if( BLOCK_SIZE(target) >= alloc_size ) {
      remove_free_block( pool, target );
      goto SPLIT_BLOCK;
    }
    target = target->next_free;
  }

  // else out of memory
#if defined(MRBC_OUT_OF_MEMORY)
  MRBC_OUT_OF_MEMORY();
#else
  static const char msg[] = "Fatal error: Out of memory.\n";
  hal_write(2, msg, sizeof(msg)-1);
#endif
  return NULL;  // ENOMEM


 FOUND_FLI_SLI:
  index = (fli << MRBC_ALLOC_SLI_BIT_WIDTH) + sli;
  assert( index < SIZE_FREE_BLOCKS );
  target = pool->free_blocks[index];
  assert( target != NULL );

 FOUND_TARGET_BLOCK:
  assert(BLOCK_SIZE(target) >= alloc_size);

  // remove free_blocks index
  pool->free_blocks[index] = target->next_free;
  if( target->next_free == NULL ) {
    pool->free_sli_bitmap[fli] &= ~(MSB_BIT1_SLI >> sli);
    if( pool->free_sli_bitmap[fli] == 0 ) pool->free_fli_bitmap &= ~(MSB_BIT1_FLI >> fli);
  }
  else {
    target->next_free->prev_free = NULL;
  }

 SPLIT_BLOCK: {
    FREE_BLOCK *release = split_block(target, alloc_size);
    if( release != NULL ) {
      SET_PREV_USED(release);
      add_free_block( pool, release );
    } else {
      FREE_BLOCK *next = PHYS_NEXT(target);
      SET_PREV_USED(next);
    }
  }

  SET_USED_BLOCK(target);
  SET_VM_ID( target, 0 );

#if defined(MRBC_DEBUG)
  memset( (uint8_t *)target + sizeof(USED_BLOCK), 0xaa,
          BLOCK_SIZE(target) - sizeof(USED_BLOCK) );
#endif
  alloc_profile();

  return (uint8_t *)target + sizeof(USED_BLOCK);
}

/* ================= verbatim, src/alloc.c 689-782 (mrbc_raw_free) ======================== */
//================================================================
/*! release memory

  @param  ptr	Return value of mrbc_raw_alloc()
*/
void mrbc_raw_free(void *ptr)
{
  MEMORY_POOL *pool = memory_pool;

#if defined(MRBC_DEBUG)
  {
    if( ptr == NULL ) {
      static const char msg[] = "mrbc_raw_free(): NULL pointer was given.\n";
      hal_write(2, msg, sizeof(msg)-1);
      return;
    }

    FREE_BLOCK *target = BLOCK_ADRS(ptr);
    if( target < (FREE_BLOCK *)BPOOL_TOP(pool) ||
	target > (FREE_BLOCK *)BPOOL_END(pool) ) {
      static const char msg[] = "mrbc_raw_free(): Outside memory pool address was specified.\n";
      hal_write(2, msg, sizeof(msg)-1);
      return;
    }

    FREE_BLOCK *block = BPOOL_TOP(pool);
    while(1) {
      if( block == target ) break;
      if( PHYS_NEXT(block) >= BPOOL_END(pool) ) break;
      block = PHYS_NEXT(block);
    }

    if( block == target ) {
      // found target block.
      if( IS_FREE_BLOCK(block) ) {  // is Free block?
        static const char msg[] = "mrbc_raw_free(): double free detected.\n";
        hal_write(2, msg, sizeof(msg)-1);
        return;
      }

      if( PHYS_NEXT(block) >= BPOOL_END(pool) ) {  // Is this a sentinel?
        static const char msg[] = "mrbc_raw_free(): no_free address was specified.\n";
        hal_write(2, msg, sizeof(msg)-1);
        return;
      }

    } else {
      // not found target block.
      if( block < target ) {
	static const char msg[] = "mrbc_raw_free(): no_free address was specified.\n";
	hal_write(2, msg, sizeof(msg)-1);
	return;
      }

      static const char msg[] = "mrbc_raw_free(): Illegal address.\n";
      hal_write(2, msg, sizeof(msg)-1);
      return;
    }

    SET_VM_ID( target, 0xff );
    memset( ptr, 0xff, BLOCK_SIZE(target) - sizeof(USED_BLOCK) );
  }
#endif

  if( ptr == NULL ) return;

  // get target block
  FREE_BLOCK *target = BLOCK_ADRS(ptr);

  // check next block, merge?
  FREE_BLOCK *next = PHYS_NEXT(target);

  if( IS_FREE_BLOCK(next) ) {
    remove_free_block( pool, next );
    merge_block(target, next);
  } else {
    SET_PREV_FREE(next);
  }

  // check prev block, merge?
  if( IS_PREV_FREE(target) ) {
    FREE_BLOCK *prev = *((FREE_BLOCK **)((uint8_t*)target - sizeof(FREE_BLOCK *)));

    assert( IS_FREE_BLOCK(prev) );
    remove_free_block( pool, prev );
    merge_block(prev, target);
    target = prev;
  }

  // target, add to index
  add_free_block( pool, target );

  alloc_profile();
}

/* forward decl of mrbc_set_vm_id -- VERBATIM (src/alloc.h:81, the VMID block) -- the real
 * prototype this TU sees via `#include "alloc.h"` in the actual project; the definition is
 * pasted AFTER the target function below, mirroring alloc.c's own file order (mrbc_set_vm_id
 * is defined later in the file than mrbc_raw_realloc). */
void mrbc_set_vm_id(void *ptr, int vm_id);

/* ========================================================================================= */
/* TARGET FUNCTION -- copied BYTE-FOR-BYTE from data_cve/cve_fcbecfe9/target/original_function.c */
/* ========================================================================================= */
__attribute__((noinline))
void * mrbc_raw_realloc(void *ptr, unsigned int size)
{
  if (ptr != NULL && size == 0) {
    mrbc_raw_free(ptr);
    return NULL;
  }

  MEMORY_POOL *pool = memory_pool;
  volatile USED_BLOCK *target = BLOCK_ADRS(ptr);
  MRBC_ALLOC_MEMSIZE_T alloc_size = size + sizeof(USED_BLOCK);
  FREE_BLOCK *next;

  // align 4 byte
  alloc_size += (-alloc_size & 3);

  // check minimum alloc size.
  if( alloc_size < MRBC_MIN_MEMORY_BLOCK_SIZE ) alloc_size = MRBC_MIN_MEMORY_BLOCK_SIZE;

  // expand? part1.
  // next phys block is free and enough size?
  if( alloc_size > BLOCK_SIZE(target) ) {
    next = PHYS_NEXT(target);
    if( IS_USED_BLOCK(next) ) goto ALLOC_AND_COPY;
    if( (BLOCK_SIZE(target) + BLOCK_SIZE(next)) < alloc_size ) goto ALLOC_AND_COPY;

    remove_free_block( pool, next );
    merge_block((FREE_BLOCK *)target, next);
  }
  next = PHYS_NEXT(target);

  // try shrink.
  FREE_BLOCK *release = split_block((FREE_BLOCK *)target, alloc_size);
  if( release != NULL ) {
    SET_PREV_USED(release);
  } else {
    SET_PREV_USED(next);
    alloc_profile();
    return ptr;
  }

  // check next block, merge?
  if( IS_FREE_BLOCK(next) ) {
    remove_free_block( pool, next );
    merge_block(release, next);
  } else {
    SET_PREV_FREE(next);
  }
  add_free_block( pool, release );
  alloc_profile();
  return ptr;


  // expand part2.
  // new alloc and copy
 ALLOC_AND_COPY: {
    void *new_ptr = mrbc_raw_alloc(size);
    if( new_ptr == NULL ) return NULL;  // ENOMEM

    memcpy(new_ptr, ptr, BLOCK_SIZE(target) - sizeof(USED_BLOCK));
    mrbc_set_vm_id(new_ptr, target->vm_id);

    mrbc_raw_free(ptr);

    return new_ptr;
  }
}
/* ==== end verbatim target function ==== */

/* ================= verbatim, src/alloc.c 938-947 (mrbc_set_vm_id) ======================= */
//================================================================
/*! set vm id

  @param  ptr	Return value of mrbc_alloc()
  @param  vm_id	vm id
*/
void mrbc_set_vm_id(void *ptr, int vm_id)
{
  SET_VM_ID( BLOCK_ADRS(ptr), vm_id );
}

/* ================= driver =================================================================
 * Reads argv[1] into a HEAP buffer (malloc, ASAN-guarded). The file format is synthetic
 * (mrbc_raw_realloc is called DIRECTLY, not through any mrubyc parser):
 *   byte0 & 1 == 1  -> TRIGGER: mrbc_raw_realloc(NULL, size) -- ptr==NULL, the exact
 *                      pre-fix-unhandled case (the fix's new
 *                      `if(ptr==NULL) return mrbc_raw_alloc(size);` branch is what this
 *                      call would need, and never gets in the vulnerable revision).
 *   byte0 & 1 == 0  -> SAFE: mrbc_raw_alloc() a real block first, then
 *                      mrbc_raw_realloc() it (ptr!=NULL) with an attacker-influenced new
 *                      size -- exercises the SAME target function on its well-formed path
 *                      (grow / shrink / in-place-resize all reachable depending on size).
 * byte1 seeds the SAFE-mode initial allocation size; byte2/byte3 seed the realloc request
 * size used in BOTH modes -- so every trigger/safe input still drives the target with
 * distinct, file-derived arguments, not a hardcoded constant.
 */
static uint8_t g_pool[16384] __attribute__((aligned(16)));

int main(int argc, char **argv)
{
  if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 64; }
  FILE *fp = fopen(argv[1], "rb");
  if (!fp) { perror("fopen"); return 64; }
  if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 64; }
  long fsz = ftell(fp);
  if (fsz < 0) { fclose(fp); return 64; }
  if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return 64; }

  size_t n = (size_t)fsz;
  unsigned char *ibuf = (unsigned char *)malloc(n ? n : 1);    /* HEAP input, ASAN-guarded */
  if (!ibuf) { fclose(fp); return 64; }
  size_t got = n ? fread(ibuf, 1, n, fp) : 0;
  fclose(fp);

  int trigger = (got >= 1) ? (ibuf[0] & 1) : 1;

  unsigned int req_size = 16;
  if (got >= 4) req_size = 1u + ((((unsigned int)ibuf[2] << 8) | ibuf[3]) % 512u);
  else if (got >= 3) req_size = 1u + (unsigned int)(ibuf[2] % 512);

  mrbc_init_alloc(g_pool, sizeof(g_pool));

  /* Call through volatile function pointers so mrbc_raw_alloc/mrbc_raw_realloc (each a
   * single-call-site function here) can't be inlined and disappear as a distinct ASAN
   * backtrace frame -- mrbc_raw_realloc is ALSO marked noinline above. Neither technique
   * touches either function's own bytes. */
  void *(*volatile vb_alloc)(unsigned int) = mrbc_raw_alloc;
  void *(*volatile vb_realloc)(void *, unsigned int) = mrbc_raw_realloc;

  void *ptr = NULL;
  if (!trigger) {
    unsigned int init_size = 1u + (unsigned int)((got >= 2 ? ibuf[1] : 8) % 200);
    ptr = vb_alloc(init_size);
    if (ptr == NULL) { free(ibuf); return 0; }   /* OOM -- shouldn't happen, exit clean */
  }

  void *r = vb_realloc(ptr, req_size);   /* trigger: ptr==NULL -> SEGV inside
                                           * mrbc_raw_realloc. safe: ptr!=NULL -> normal
                                           * grow/shrink/in-place, returns cleanly. */
  (void)r;

  free(ibuf);
  return 0;
}
