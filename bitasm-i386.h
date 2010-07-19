#if !defined HAVE_BITASM_I386_H__
#define      HAVE_BITASM_I386_H__

#if !defined HAVE_BITASM_H__
#error 'Do not include directly, included by bitasm.h'
#endif  // !defined HAVE_BITASM_H__

static inline unsigned long asm_bsf(unsigned long x)
// Bit Scan Forward
{
    asm ("bsfl %0, %0" : "=r" (x) : "0" (x));
    return x;
}
// -------------------------


static inline unsigned long asm_bsr(unsigned long x)
// Bit Scan Reverse
{
    asm ("bsrl %0, %0" : "=r" (x) : "0" (x));
    return x;
}
// -------------------------


static inline unsigned long asm_bswap(unsigned long x)
// byte swap
{
    asm ("bswap %0" : "=r" (x) : "0" (x));
    return x;
}
// -------------------------


static inline unsigned long asm_rol(unsigned long x, unsigned long r)
// Rotate Left
{
    asm ("roll   %%cl, %0" : "=r" (x) : "0" (x), "c" (r));
    return x;
}
// -------------------------


static inline unsigned long asm_ror(unsigned long x, unsigned long r)
// Rotate Right
{
    asm ("rorl   %%cl, %0" : "=r" (x) : "0" (x), "c" (r));
    return x;
}
// -------------------------


static inline unsigned long asm_parity(unsigned long x)
// Return the parity of x (which is the
// _complement_ of x86's parity flag).
// As parity is for the low byte only,
// therefore we need to prepend
// x ^= (x>>16);  x ^= (x>>8);
// in the code
{
    x ^= (x>>16);
    x ^= (x>>8);
    asm ("addl  $0, %0  \n"
         "setnp %%al    \n"
         "movzx %%al, %0"
         : "=r" (x) : "0" (x) : "eax");

    return x;
}
// -------------------------


static inline unsigned long asm_bt(const unsigned long *f, unsigned long i)
// Bit Test
{
    unsigned long ret;
    asm ( "btl  %2, %1 \n" // carry = 0 or 1
          "sbbl %0, %0"    // ret = 0 or -1
          : "=r" (ret)
          : "m" (*f), "r" (i) );
    return ret;
}
// -------------------------

static inline unsigned long asm_bts(unsigned long *f, unsigned long i)
// Bit Test and Set
{
    unsigned long ret;
    asm ( "btsl %2, %1 \n"
          "sbbl %0, %0"
          : "=r" (ret)
          : "m" (*f), "r" (i) );
    return ret;
}
// -------------------------

static inline void asm_b_s(unsigned long *f, unsigned long i)
// Bit Set
{
    asm ( "btsl  %1, %0 \n"
          : /* void */
          : "m" (*f), "r" (i) );
}
// -------------------------

static inline unsigned long asm_btr(unsigned long *f, unsigned long i)
// Bit Test and Reset
{
    unsigned long ret;
    asm ( "btrl  %2, %1 \n"
          "sbbl %0, %0"
          : "=r" (ret)
          : "m" (*f), "r" (i) );
    return ret;
}
// -------------------------

static inline void asm_b_r(unsigned long *f, unsigned long i)
// Bit Reset
{
    asm ( "btrl  %1, %0 \n"
          : /* void */
          : "m" (*f), "r" (i) );
}
// -------------------------

static inline unsigned long asm_btc(unsigned long *f, unsigned long i)
// Bit Test and Complement
{
    unsigned long ret;
    asm ( "btcl  %2, %1 \n"
          "sbbl %0, %0"
          : "=r" (ret)
          : "m" (*f), "r" (i) );
    return ret;
}
// -------------------------

static inline void asm_b_c(unsigned long *f, unsigned long i)
// Bit Complement
{
    asm ( "btcl  %1, %0 \n"
          : /* void */
          : "m" (*f), "r" (i) );
}
// -------------------------


#endif  // !defined HAVE_BITASM_I386_H__
