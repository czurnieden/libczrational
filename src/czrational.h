#ifndef _CZRATIONAL_H
#define _CZRATIONAL_H

#include <tommath.h>
#include <stdarg.h>

#ifndef DIGIT_SIZE
#define DIGIT_SIZE (1<<DIGIT_BIT)
#endif

/* 
     The main structure of the rational numbers with its members
     aptfully named.
     On the other side is the name of the type itself ...

     The "sign" makes use of the macros used by libtommath:
       MP_ZPOS for positive rationals
       MP_NEG  for negative rationals

     Zero has the special number: "0/1"
     Zero is positive.

     Undefined/Error has the special number "0/0" with undefined sign.
 */
typedef struct  {
    int sign;
    mp_int numerator;
    mp_int denominator;
}  mp_rat;

/*
  Initializing is done just like in libtommath.
  Even some of the code of the individual functions is similar.
*/
int mpq_init(mp_rat *a);
int mpq_init_multi(mp_rat *mp, ...) ;
void mpq_clear(mp_rat *a);
void mpq_clear_multi(mp_rat *mp, ...);

/* Prints the rational to stdout. NOT followed by a newline! */
void mpq_print(mp_rat * a);
/* Prints the rational to stream. NOT followed by a newline! */
void mpq_fprint(mp_rat * a,FILE *stream);
/* Prints the rational to stream in radix radix. NOT followed by a newline! */
void mpq_fwrite(mp_rat * a,int radix,FILE *stream);


/* 
  Sets mp_rat->sign according to sign of num+den and makes num/den positive
  Does ignore the original sign!
  More of an internal function used when filling the rational with numbers
  of sign unknown at compile time.
  Use with care.
 */
void mpq_normalize_sign(mp_rat *a);
/* returns sign of mp_rat a */
int mpq_get_sign(mp_rat *a);
/* sets sign of mp_rat a to sign given in "sign", returns old sign */
int mpq_set_sign(mp_rat *a, int sign);
/* reverses sign of mp_rat a */
int mpq_neg(mp_rat *a);


/* sets given mp_int b as the numerator in mp_rat a */
int mpq_set_num(mp_rat *a, mp_int *b);
/* sets given mp_int b as the denominator in mp_rat a */
int mpq_set_den(mp_rat *a, mp_int *b);
/* sets given mp_int p,q as numerator and denominator respectively in mp_rat a */
int mpq_set(mp_rat *a, mp_int *p, mp_int *q);

/* 
    Sets given long b as the numerator in mp_rat a.
    Uses the libtommath function  mp_set_int() which assumes 32 bit longs
    and a 28 large mp_digit!
 */
int mpq_set_num_int(mp_rat *a, long b);
/* sets given unsigned long b as the denominator in mp_rat a but see above*/
int mpq_set_den_int(mp_rat *a, long b);
/* sets given unsigned longs p,q as the numerator,denominator in mp_rat a
   but see above*/
int mpq_set_int(mp_rat *a, long p,long q);

/* sets b = a, by deep copy*/
int mpq_copy(mp_rat *a, mp_rat *b);

/* sets b = a, by pointer exchange only*/
void mpq_exch(mp_rat *a, mp_rat *b );

/* TODO: put in tommath.h */
#define mp_isone(a) (((a)->used == 1 && (a)->dp[0] == 1) ? MP_YES : MP_NO)

/* Last prime < 1000 */
#define MPQ_DIVISION_BY_ZERO -997

/* 
   Some functions like the one implemented with the binary splitting algorithm
   cannot return the error and set this variable instead.
 */
int errornumber;
/*
  Reduce a fraction.
  Computes one GCD and two probably large divisions, so use with care.
*/
int mpq_reduce(mp_rat *a);

/*
  Inverse of the fraction by exchanging pointers of numerator and denominator.
  Returns MPQ_DIVISION_BY_ZERO if numerator is zero
 */
int mpq_inverse(mp_rat *a);

/*
    Tests if the fraction reduces to unity. Does not check sign, so it can
    be 1 and -1.
 */
int mpq_isone(mp_rat *a);
/* Tests if fraction is special number zero */
int mpq_iszero(mp_rat *a);
/* Tests if denominator is one */
int mpq_isinteger(mp_rat *a);

/* Tests if the fraction is the special number used for "undefined" */
int mpq_isundefined(mp_rat *a);

/* Tests if the fraction is negative*/
int mpq_isneg(mp_rat *a);

/*
  This is a computationally expensive function.
  returns
    MP_EQ if equal
    MP_LT if a > b
    MP_GT if a < b
  Not tested, use with care!
*/
int mpq_cmp(mp_rat *a, mp_rat *b);

/* c = a + b */
int mpq_add(mp_rat *a, mp_rat *b, mp_rat *c);
/* c = a - b */
int mpq_sub(mp_rat *a, mp_rat *b, mp_rat *c);
/* c = a * b */
int mpq_mul(mp_rat *a, mp_rat *b, mp_rat *c);
/* c = a / b */
int mpq_div(mp_rat *a, mp_rat *b, mp_rat *c);

/*Not defined if you use the original version of libtommath, so we try it here*/
#ifndef DIGIT_SIZE
#define DIGIT_SIZE (1<<DIGIT_BIT)
#endif


/*  c = a^d

    Uses the libtommath function mp_expt_d (mp_int * a, mp_digit b, mp_int * c)
    which limits the size of d to DIGIT_SIZE. The default of libtommath is
    2^28 but could be as small as 2^8!

    BTW: we see 0^0 as undefined in this house!
 */
int mpq_pow_d(mp_rat *a, long d, mp_rat *c);

/* 
    Puts the Bernoulli number B_n into c
    Uses the Brent-Harvey Algorithm which is based on the Tangent numbers and
    is fast enough up to about B_{1000}. A couple of seconds, depending on
    horsepower.
    Calculates all of the numbes up to "limit" the first time.
 */
int mpq_bernoulli(unsigned long n, mp_rat *c);
/* clears and frees Bernoulli-cache */
void mpq_bernoulli_free();
/* 
    Puts the Euler number E_n into c
    Uses the Brent-Harvey Algorithm which is based on the Secant numbers and
    is fast enough up to about E_{2000}. A couple of seconds, depending on
    horsepower.
    Calculates all of the numbes up to "limit" the first time.
 */
int mpq_euler(unsigned long n, mp_rat * c);
/* Euler numbers are integers, so ... */
int mp_euler_int(unsigned long n, mp_int * c);
/* clears and frees Euler-cache */
void mpq_euler_free(void);
/* Partial harmonic series */
int mpq_harmonics(unsigned long n, mp_rat * c);
/*******************************************************************************
   So far with the exact calculations. From now on a limit is introduced.
   There is no default value for it. Well, actually there is but it is zero.
   You have to set it explicitly and at the very beginning!
 ******************************************************************************/

#ifndef MPI_LOG2
#   define MPI_LOG2 3.321928094887362347870319429489390175864831393024580612054
#endif
#include <math.h>

/* "eps" assumed to be precision in number of decimal digits */
void mpq_set_epsilon(int eps);
/* returns the precision as the number of binary digits */
int mpq_get_epsilon(void);

/* c = a^(1/2) */
int mpq_sqrt(mp_rat *a, mp_rat *c);


#endif
