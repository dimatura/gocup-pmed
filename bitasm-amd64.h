#if !defined HAVE_BITASM_AMD64_H__
#define      HAVE_BITASM_AMD64_H__

#if !defined HAVE_BITASM_H__
#error 'Do not include directly, included by bitasm.h'
#endif  // !defined HAVE_BITASM_H__

// AMD 24592:
// The BSF and BSR instructions search a source operand for the
// least-significant (BSF) or most-significant (BSR) bit that is set
// to 1. If a set bit is found, its bit index is loaded into the
// destination operand, and the zero flag (ZF) is set. If no set bit
// is found , the zero flag is cleared and the contents of the
// destination are undefined.

static inline unsigned long asm_bsf(unsigned long x)
// Bit Scan Forward
{
    asm ("bsfq %0, %0" : "=r" (x) : "0" (x));
    return x;
}
// -------------------------


static inline unsigned long asm_bsr(unsigned long x)
// Bit Scan Reverse
{
    asm ("bsrq %0, %0" : "=r" (x) : "0" (x));
    return x;
}
// -------------------------


static inline unsigned long asm_bswap(unsigned long x)
// Byte swap
{
    asm ("bswap %0" : "=r" (x) : "0" (x));
    return x;
}
// -------------------------


static inline unsigned long asm_rol(unsigned long x, unsigned long r)
// Rotate Left
{
    asm ("rolq   %%cl, %0" : "=r" (x) : "0" (x), "c" (r));
    return x;
}
// -------------------------


static inline unsigned long asm_ror(unsigned long x, unsigned long r)
// Rotate Right
{
    asm ("rorq   %%cl, %0" : "=r" (x) : "0" (x), "c" (r));
    return x;
}
// -------------------------


static inline unsigned long asm_parity(unsigned long x)
// Return the parity of x (which is the
// _complement_ of AMD64's parity flag).
// As parity is for the low byte only,
// therefore we need to prepend
// x ^= (x>>16);  x ^= (x>>8);
// in the code
{
    x ^= (x>>32);
    x ^= (x>>16);
    x ^= (x>>8);
    asm ("addq  $0, %0  \n"
         "setnp %%al    \n"
         "movzx %%al, %0"
         : "=r" (x) : "0" (x) : "rax");

    return x;
}
// -------------------------

// AMD 24592:
// The BTx instructions copy a specified bit in the first operand to
// the carry flag (CF) and leave the source bit unchanged (BT), or
// complement the source bit (BTC), or clear the source bit to 0
// (BTR), or set the source bit to 1 (BTS).

static inline unsigned long asm_bt(const unsigned long *f, unsigned long i)
// Bit Test
{
    unsigned long ret;
    asm ( "btq  %2, %1 \n" // carry = 0 or 1
          "sbbq %0, %0"    // ret = 0 or -1
          : "=r" (ret)
          : "m" (*f), "r" (i) );
    return ret;
}
// -------------------------

static inline unsigned long asm_bts(unsigned long *f, unsigned long i)
// Bit Test and Set
{
    unsigned long ret;
    asm ( "btsq %2, %1 \n"
          "sbbq %0, %0"
          : "=r" (ret)
          : "m" (*f), "r" (i) );
    return ret;
}
// -------------------------

static inline void asm_b_s(unsigned long *f, unsigned long i)
// Bit Set
{
    asm ( "btsq  %1, %0 \n"
          : /* void */
          : "m" (*f), "r" (i) );
}
// -------------------------

static inline unsigned long asm_btr(unsigned long *f, unsigned long i)
// Bit Test and Reset
{
    unsigned long ret;
    asm ( "btrq  %2, %1 \n"
          "sbbq %0, %0"
          : "=r" (ret)
          : "m" (*f), "r" (i) );
    return ret;
}
// -------------------------

static inline void asm_b_r(unsigned long *f, unsigned long i)
// Bit Reset
{
    asm ( "btrq  %1, %0 \n"
          : /* void */
          : "m" (*f), "r" (i) );
}
// -------------------------

static inline unsigned long asm_btc(unsigned long *f, unsigned long i)
// Bit Test and Complement
{
    unsigned long ret;
    asm ( "btcq  %2, %1 \n"
          "sbbq %0, %0"
          : "=r" (ret)
          : "m" (*f), "r" (i) );
    return ret;
}
// -------------------------

static inline void asm_b_c(unsigned long *f, unsigned long i)
// Bit Complement
{
    asm ( "btcq  %1, %0 \n"
          : /* void */
          : "m" (*f), "r" (i) );
}
// -------------------------


#endif //  HAVE_BITASM_AMD64_H__
