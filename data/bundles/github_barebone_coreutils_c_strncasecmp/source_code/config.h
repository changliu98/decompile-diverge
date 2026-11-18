/* Auto-generated minimal gnulib config.h stub for standalone leaf-module builds
 * (Decompile-Diverge github axis). Defines _GL_CONFIG_H_INCLUDED gate + neutralises the _GL_*
 * attribute/inline macros the resolved coreutils/gnulib modules use. */
#ifndef _GL_CONFIG_H_INCLUDED
#define _GL_CONFIG_H_INCLUDED 1
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#if !defined __GNUC_PREREQ
#define __GNUC_PREREQ(a,b) 0
#endif
#include <stdalign.h>
#define _STRING_ARCH_unaligned 1
typedef ptrdiff_t idx_t;
/* --- inline machinery --- */
#define _GL_INLINE static inline
#define _GL_EXTERN_INLINE static inline
#define _GL_INLINE_HEADER_BEGIN
#define _GL_INLINE_HEADER_END
/* --- semantic macros (real definitions, NOT neutralised) --- */
#define _GL_CMP(n1, n2) (((n1) > (n2)) - ((n1) < (n2)))
/* --- neutralised attribute / arg macros --- */
#ifndef _GL_ADD_OVERFLOW
#define _GL_ADD_OVERFLOW(...)
#endif
#ifndef _GL_ATTRIBUTE_
#define _GL_ATTRIBUTE_
#endif
#ifndef _GL_ATTRIBUTE_ALLOC_SIZE
#define _GL_ATTRIBUTE_ALLOC_SIZE(...)
#endif
#ifndef _GL_ATTRIBUTE_ALWAYS_INLINE
#define _GL_ATTRIBUTE_ALWAYS_INLINE
#endif
#ifndef _GL_ATTRIBUTE_ARTIFICIAL
#define _GL_ATTRIBUTE_ARTIFICIAL
#endif
#ifndef _GL_ATTRIBUTE_COLD
#define _GL_ATTRIBUTE_COLD
#endif
#ifndef _GL_ATTRIBUTE_CONST
#define _GL_ATTRIBUTE_CONST
#endif
#ifndef _GL_ATTRIBUTE_COUNTED_BY
#define _GL_ATTRIBUTE_COUNTED_BY(...)
#endif
#ifndef _GL_ATTRIBUTE_DEALLOC
#define _GL_ATTRIBUTE_DEALLOC(...)
#endif
#ifndef _GL_ATTRIBUTE_DEALLOC_FREE
#define _GL_ATTRIBUTE_DEALLOC_FREE
#endif
#ifndef _GL_ATTRIBUTE_DEPRECATED
#define _GL_ATTRIBUTE_DEPRECATED
#endif
#ifndef _GL_ATTRIBUTE_ERROR
#define _GL_ATTRIBUTE_ERROR(...)
#endif
#ifndef _GL_ATTRIBUTE_EXTERNALLY_VISIBLE
#define _GL_ATTRIBUTE_EXTERNALLY_VISIBLE
#endif
#ifndef _GL_ATTRIBUTE_FALLTHROUGH
#define _GL_ATTRIBUTE_FALLTHROUGH
#endif
#ifndef _GL_ATTRIBUTE_FORMAT
#define _GL_ATTRIBUTE_FORMAT(...)
#endif
#ifndef _GL_ATTRIBUTE_H
#define _GL_ATTRIBUTE_H
#endif
#ifndef _GL_ATTRIBUTE_LEAF
#define _GL_ATTRIBUTE_LEAF
#endif
#ifndef _GL_ATTRIBUTE_MALLOC
#define _GL_ATTRIBUTE_MALLOC
#endif
#ifndef _GL_ATTRIBUTE_MAYBE_UNUSED
#define _GL_ATTRIBUTE_MAYBE_UNUSED
#endif
#ifndef _GL_ATTRIBUTE_MAY_ALIAS
#define _GL_ATTRIBUTE_MAY_ALIAS
#endif
#ifndef _GL_ATTRIBUTE_NODISCARD
#define _GL_ATTRIBUTE_NODISCARD
#endif
#ifndef _GL_ATTRIBUTE_NOINLINE
#define _GL_ATTRIBUTE_NOINLINE
#endif
#ifndef _GL_ATTRIBUTE_NONNULL
#define _GL_ATTRIBUTE_NONNULL(...)
#endif
#ifndef _GL_ATTRIBUTE_NONNULL_IF_NONZERO
#define _GL_ATTRIBUTE_NONNULL_IF_NONZERO(...)
#endif
#ifndef _GL_ATTRIBUTE_NONSTRING
#define _GL_ATTRIBUTE_NONSTRING
#endif
#ifndef _GL_ATTRIBUTE_NOTHROW
#define _GL_ATTRIBUTE_NOTHROW
#endif
#ifndef _GL_ATTRIBUTE_PACKED
#define _GL_ATTRIBUTE_PACKED
#endif
#ifndef _GL_ATTRIBUTE_PURE
#define _GL_ATTRIBUTE_PURE
#endif
#ifndef _GL_ATTRIBUTE_REPRODUCIBLE
#define _GL_ATTRIBUTE_REPRODUCIBLE
#endif
#ifndef _GL_ATTRIBUTE_RETURNS_NONNULL
#define _GL_ATTRIBUTE_RETURNS_NONNULL
#endif
#ifndef _GL_ATTRIBUTE_SENTINEL
#define _GL_ATTRIBUTE_SENTINEL(...)
#endif
#ifndef _GL_ATTRIBUTE_UNSEQUENCED
#define _GL_ATTRIBUTE_UNSEQUENCED
#endif
#ifndef _GL_ATTRIBUTE_WARNING
#define _GL_ATTRIBUTE_WARNING(...)
#endif
#ifndef _GL_BINARY_OP_OVERFLOW
#define _GL_BINARY_OP_OVERFLOW(...)
#endif
#ifndef _GL_DIVIDE_OVERFLOW
#define _GL_DIVIDE_OVERFLOW(...)
#endif
#ifndef _GL_EXPR_SIGNED
#define _GL_EXPR_SIGNED(...)
#endif
#ifndef _GL_HAS_BUILTIN_ADD_OVERFLOW
#define _GL_HAS_BUILTIN_ADD_OVERFLOW
#endif
#ifndef _GL_HAS_BUILTIN_MUL_OVERFLOW
#define _GL_HAS_BUILTIN_MUL_OVERFLOW
#endif
#ifndef _GL_HAS_BUILTIN_OVERFLOW_P
#define _GL_HAS_BUILTIN_OVERFLOW_P(...)
#endif
#ifndef _GL_HAVE___TYPEOF__
#define _GL_HAVE___TYPEOF__
#endif
#ifndef _GL_INTPROPS_H
#define _GL_INTPROPS_H
#endif
#ifndef _GL_INTPROPS_INTERNAL_H
#define _GL_INTPROPS_INTERNAL_H
#endif
#ifndef _GL_INT_ADD_RANGE_OVERFLOW
#define _GL_INT_ADD_RANGE_OVERFLOW(...)
#endif
#ifndef _GL_INT_ADD_WRAPV
#define _GL_INT_ADD_WRAPV(...)
#endif
#ifndef _GL_INT_CONVERT
#define _GL_INT_CONVERT(...)
#endif
#ifndef _GL_INT_MAXIMUM
#define _GL_INT_MAXIMUM(...)
#endif
#ifndef _GL_INT_MINIMUM
#define _GL_INT_MINIMUM(...)
#endif
#ifndef _GL_INT_MULTIPLY_RANGE_OVERFLOW
#define _GL_INT_MULTIPLY_RANGE_OVERFLOW(...)
#endif
#ifndef _GL_INT_MULTIPLY_WRAPV
#define _GL_INT_MULTIPLY_WRAPV(...)
#endif
#ifndef _GL_INT_NEGATE_OVERFLOW
#define _GL_INT_NEGATE_OVERFLOW(...)
#endif
#ifndef _GL_INT_NEGATE_RANGE_OVERFLOW
#define _GL_INT_NEGATE_RANGE_OVERFLOW(...)
#endif
#ifndef _GL_INT_OP_CALC
#define _GL_INT_OP_CALC(...)
#endif
#ifndef _GL_INT_OP_WRAPV
#define _GL_INT_OP_WRAPV(...)
#endif
#ifndef _GL_INT_OP_WRAPV_LONGISH
#define _GL_INT_OP_WRAPV_LONGISH(...)
#endif
#ifndef _GL_INT_OP_WRAPV_SMALLISH
#define _GL_INT_OP_WRAPV_SMALLISH(...)
#endif
#ifndef _GL_INT_OP_WRAPV_VIA_UNSIGNED
#define _GL_INT_OP_WRAPV_VIA_UNSIGNED(...)
#endif
#ifndef _GL_INT_SUBTRACT_RANGE_OVERFLOW
#define _GL_INT_SUBTRACT_RANGE_OVERFLOW(...)
#endif
#ifndef _GL_INT_SUBTRACT_WRAPV
#define _GL_INT_SUBTRACT_WRAPV(...)
#endif
#ifndef _GL_MULTIPLY_OVERFLOW
#define _GL_MULTIPLY_OVERFLOW(...)
#endif
#ifndef _GL_REMAINDER_OVERFLOW
#define _GL_REMAINDER_OVERFLOW(...)
#endif
#ifndef _GL_SIGNED_INT_MAXIMUM
#define _GL_SIGNED_INT_MAXIMUM(...)
#endif
#ifndef _GL_SIGNED_TYPE_OR_EXPR
#define _GL_SIGNED_TYPE_OR_EXPR(...)
#endif
#ifndef _GL_STDCKDINT_H
#define _GL_STDCKDINT_H
#endif
#ifndef _GL_SUBTRACT_OVERFLOW
#define _GL_SUBTRACT_OVERFLOW(...)
#endif
#ifndef _GL_TYPE_SIGNED
#define _GL_TYPE_SIGNED(...)
#endif
#ifndef _GL_TYPE_WIDTH
#define _GL_TYPE_WIDTH(...)
#endif
#ifndef _GL_U64_INLINE
#define _GL_U64_INLINE
#endif
#ifndef _GL_U64_MASK32
#define _GL_U64_MASK32
#endif
#ifndef _GL_UNNAMED
#define _GL_UNNAMED(...)
#endif
#ifndef _GL_UNSIGNED_NEG_MULTIPLE
#define _GL_UNSIGNED_NEG_MULTIPLE(...)
#endif
#ifndef _GL__GENERIC_BOGUS
#define _GL__GENERIC_BOGUS
#endif
#endif /* _GL_CONFIG_H_INCLUDED */
