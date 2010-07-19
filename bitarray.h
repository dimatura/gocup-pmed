#if !defined HAVE_BITARRAY_H__
#define      HAVE_BITARRAY_H__

#include "bitsperlong.h"
#include "bitasm.h"

// suppress assembler instructions, for timing purposes:
//#undef  BITS_USE_ASM

#define  DIVMOD(n, d, bm) \
unsigned long d = n / BITS_PER_LONG; \
unsigned long bm = 1UL << (n % BITS_PER_LONG);

#define  DIVMOD_TEST(n, d, bm) \
unsigned long d = n / BITS_PER_LONG; \
unsigned long bm = 1UL << (n % BITS_PER_LONG); \
unsigned long t = bm & f_[d];

#define CHECK  0  // define to disable check of out of bounds access
//#define CHECK  1  // define to handle out of bounds access
//#define CHECK  2  // define to fail with out of bounds access

class bitarray
// Bit-array class mostly for use as memory saving array of boolean values.
// Valid index is 0...nb_-1 (as usual in C arrays).
{
public:
    unsigned long *f_;   // bit bucket
    unsigned long n_;    // number of bits
    unsigned long nfw_;  // number of words where all bits are used, may be zero
    unsigned long mp_;   // mask for partially used word if there is one, else zero
    // (ones are at the positions of the _unused_ bits)
    bool myfq_;  // whether f[] was allocated by class

    static bool use_asm_q()
    {
#ifdef  BITS_USE_ASM
        return true;
#else
        return false;
#endif
    }

private:
    unsigned long ctor_core(unsigned long nbits)
    {
        n_ = nbits;

        // nw_: number of words (incl. partially used), nw>=1
        unsigned long nw = n_ / BITS_PER_LONG;       // number of words

        // nbl_: number of bits used in last (partially used) word, 0 if mw==mfw
        unsigned long nbl = n_ - nw*BITS_PER_LONG;  // number of bits used in last word
        nfw_ = nw;  // number of fully used words

        if ( 0!=nbl )  // there is a partially used word
        {
            ++nw;  // increase total number of words
            mp_ = (~0UL) >> (BITS_PER_LONG-nbl);  // correct mask for last word
        }
        else  mp_ = 0UL;

        return nw;
    }

    bitarray(const bitarray& b);
    bitarray& operator=(const bitarray& b);


public:
    bitarray(unsigned long nbits, unsigned long *f=0) :
        f_(0),
        n_(0),
        nfw_(0),
        mp_(0),
        myfq_(false)
    // nbits must be nonzero
    {
        unsigned long nw = ctor_core(nbits);
        if ( f!=0 )
        {
            f_ = f;
            myfq_ = false;
        }
        else
        {
            f_ = new unsigned long[nw];
            myfq_ = true;
        }
    }

    ~bitarray()  { if ( myfq_ ) delete [] f_; }


    unsigned long test(unsigned long n)  const
    // Test whether n-th bit set.
    {
#ifdef  BITS_USE_ASM
        return asm_bt(f_, n);
#else
        DIVMOD_TEST(n, d, bm);
        return  t;
#endif
    }


    void set(unsigned long n)
    // Set n-th bit.
    {
#ifdef  BITS_USE_ASM
        asm_b_s(f_, n);
#else
        DIVMOD(n, d, bm);
        f_[d] |= bm;
#endif
    }


    void clear(unsigned long n)
    // Clear n-th bit.
    {
#ifdef  BITS_USE_ASM
        asm_b_r(f_, n);
#else
        DIVMOD(n, d, bm);
        f_[d] &= ~bm;
#endif
    }

    void change(unsigned long n)
    // Toggle n-th bit.
    {
#ifdef  BITS_USE_ASM
        asm_b_c(f_, n);
#else
        DIVMOD(n, d, bm);
        f_[d] ^= bm;
#endif
    }


    unsigned long test_set(unsigned long n)
    // Test whether n-th bit is set and set it.
    {
#ifdef  BITS_USE_ASM
        return asm_bts(f_, n);
#else
        DIVMOD_TEST(n, d, bm);
        f_[d] |= bm;
        return  t;
#endif
    }


    unsigned long test_clear(unsigned long n)
    // Test whether n-th bit is set and clear it.
    {
#ifdef  BITS_USE_ASM
        return asm_btr(f_, n);
#else
        DIVMOD_TEST(n, d, bm);
        f_[d] &= ~bm;
        return  t;
#endif
    }


    unsigned long test_change(unsigned long n)
    // Test whether n-th bit is set and toggle it.
    {
#ifdef  BITS_USE_ASM
        return asm_btc(f_, n);
#else
        DIVMOD_TEST(n, d, bm);
        f_[d] ^= bm;
        return  t;
#endif
    }

    void clear_all()
    // Clear all bits.
    {
        for (unsigned long k=0; k<nfw_; ++k)  f_[k] = 0;
        if ( mp_ )  f_[nfw_] = 0;
    }

    void set_all()
    // Set all bits.
    {
        for (unsigned long k=0; k<nfw_; ++k)  f_[k] = ~0UL;
        if ( mp_ )  f_[nfw_] = ~0UL;
    }

    unsigned long all_set_q()  const
    // Return whether all bits are set.
    {
        for (unsigned long k=0; k<nfw_; ++k)  if ( ~f_[k] )  return 0;
        if ( mp_ )
        {
            unsigned long z = f_[nfw_] & mp_;
            if ( z!=mp_ )  return 0;
        }
        return  1;
    }

    unsigned long all_clear_q()  const
    // Return whether all bits are clear
    {
        for (unsigned long k=0; k<nfw_; ++k)  if ( f_[k] )  return 0;
        if ( mp_ )
        {
            unsigned long z = f_[nfw_] & mp_;
            if ( z!=0 )  return 0;
        }
        return  1;
    }

    unsigned long next_set(unsigned long n)  const
    // Return index of next set or value beyond end.
    // Note: the given index n is included in the search
    {
        while ( (n<n_) && (!test(n)) )  ++n;
        return  n;
    }

    unsigned long next_clear(unsigned long n)  const
    // Return index of next clear or value beyond end.
    // Note: the given index n is included in the search
    {
        while ( (n<n_) && (test(n)) )  ++n;
        return  n;
    }

};
// -------------------------

#undef  DIVMOD
#undef  DIVMOD_TEST

#endif // !defined HAVE_BITARRAY_H__
