#include "czrational.h"
#include <stdarg.h>

static unsigned long bern_array_size = 0;
static mp_rat *bern_array;

static int bhbern(unsigned long limit)
{
  mp_int tmp, A, U, E;
  mp_rat *T;
  unsigned long j, k, alloc_mem;
  int e, counter = 0;

  if (limit < bern_array_size) {
    printf("Cache hit: %lu\n", limit);
    return MP_OKAY;
  }
  /* TODO: use it! ;-) 
   * if(bern_array_size == 0 && limit < 100){
   * alloc_mem = sizeof(mp_rat) * (100 + 1)*2;
   * }
   * else{
   * alloc_mem = sizeof(mp_rat) * (limit + 101)*2;
   * }
   */
  alloc_mem = sizeof(mp_rat) * (limit + 2) * 2;
  T = malloc(alloc_mem);
  if (T == NULL) {
    return MP_MEM;
  }
  /* For sake of simplicity */
  bern_array = malloc(alloc_mem / 2 + 2);
  if (bern_array == NULL) {
    return MP_MEM;
  }
  /* This algorithm starts at B_2 = 1/6 */
  /* B_0 = 1 */
  if ((e = mpq_init(&bern_array[counter])) != MP_OKAY) {
    return e;
  }
  if ((e = mpq_set_int(&bern_array[counter++], 1, 1)) != MP_OKAY) {
    return e;
  }
  /* B_1 = -1/2 */
  if ((e = mpq_init(&bern_array[counter])) != MP_OKAY) {
    return e;
  }
  if ((e = mpq_set_int(&bern_array[counter], 1, 2)) != MP_OKAY) {
    return e;
  }
  (bern_array[counter++]).sign = MP_NEG;

  for (k = 0; k <= limit; k++) {
    if ((e = mpq_init(&T[k])) != MP_OKAY) {
      return e;
    }
  }
  if ((e = mpq_set_int(&T[1], 1, 1)) != MP_OKAY) {
    return e;
  }
  for (k = 2; k < limit; k++) {
    /* T[k] = (k-1)*T[k-1] */
    if ((e =
	 mp_mul_d(&T[k - 1].numerator, (k - 1), &T[k].numerator)) != MP_OKAY) {
      return e;
    }
    if (((&T[k])->numerator).sign == MP_NEG) {
      (T[k]).sign = MP_NEG;
    }
  }

  if ((e = mp_init(&tmp)) != MP_OKAY) {
    return e;
  }

  for (k = 2; k < limit - 1; k++) {
    for (j = k; j < limit; j++) {
      /* T[j] =  (j-k)*T[j-1]  +   (j-k+2)*T[j] */
      /* tmp  =  (j-k)*T[j-1]  */
      if ((e = mp_mul_d(&T[j - 1].numerator, (j - k), &tmp)) != MP_OKAY) {
	return e;
      }
      /* T[j] =   (j-k+2)*T[j] */
      if ((e = mp_mul_d(&T[j].numerator, (j - k + 2),
			&T[j].numerator)) != MP_OKAY) {
	return e;
      }
      /* T[j] =   T[j]  + tmp */
      if ((e = mp_add(&T[j].numerator, &tmp, &T[j].numerator)) != MP_OKAY) {
	return e;
      }
      if (((&T[k])->numerator).sign == MP_NEG) {
	(T[k]).sign = MP_NEG;
      }
    }
  }

  if ((e = mp_init_multi(&E, &A, &U, NULL)) != MP_OKAY) {
    return e;
  }

  /* E = -2; U = 1 */
  if ((e = mp_set_int(&E, 2)) != MP_OKAY) {
    return e;
  }
  if ((e = mp_neg(&E, &E)) != MP_OKAY) {
    return e;
  }

  if ((e = mp_set_int(&U, 1)) != MP_OKAY) {
    return e;
  }

  for (k = 1; k < limit - 1; k++) {
    /* U = 4*U */
    if ((e = mp_mul_d(&U, 4, &U)) != MP_OKAY) {
      return e;
    }

    /*  A = U*(U-1) */
    if ((e = mp_sub_d(&U, 1, &tmp)) != MP_OKAY) {
      return e;
    }

    if ((e = mp_mul(&U, &tmp, &A)) != MP_OKAY) {
      return e;
    }

    /* E = -E */
    if ((e = mp_neg(&E, &E)) != MP_OKAY) {
      return e;
    }

    /* result = (E*T[k]*k) / (A) */
    if ((e = mp_mul_d(&E, k, &tmp)) != MP_OKAY) {
      return e;
    }

    if ((e = mp_mul(&tmp, &T[k].numerator, &tmp)) != MP_OKAY) {
      return e;
    }

    if (((&T[k])->numerator).sign == MP_NEG) {
      (T[k]).sign = MP_NEG;
    }
    if ((e = mpq_init(&bern_array[counter])) != MP_OKAY) {
      return e;
    }
    if ((e = mpq_set(&bern_array[counter++], &tmp, &A)) != MP_OKAY) {
      return e;
    }

  }
  /* realloc bern_array?
   * bern_array= realloc(bern_array,sizeof(mp_rat) * (counter+2));
   * if(bern_array == NULL){
   * return MP_MEM;
   * } 
   */
  bern_array_size = counter;

  /* It is deemed good style to clean up after work */
  for (k = 0; k < limit; k++) {
    mpq_clear(&T[k]);
  }
  free(T);
  mp_clear_multi(&tmp, &E, &A, &U, NULL);
  return MP_OKAY;
}

int mpq_bernoulli(unsigned long n, mp_rat * c)
{
  int e, k;
  /* all odd Bernoulli numbers are zero except B_1 */
  if ((n & 0x1) && n != 1) {
    mpq_set_int(c, 0, 1);
    return MP_OKAY;
  }
  if ((e = bhbern(n)) != MP_OKAY) {
    return e;
  }
  /* It simplifies things a bit to get the exceptions out of the way */
  if (n < 2) {
    if ((e = mpq_copy(&bern_array[n], c)) != MP_OKAY) {
      return e;
    }
    return MP_OKAY;
  }
  k = n / 2 + 1;
  if ((e = mpq_copy(&bern_array[k], c)) != MP_OKAY) {
    return e;
  }
  return MP_OKAY;
}

void mpq_bernoulli_free()
{
  unsigned long i = 0;
  for (; i < bern_array_size; i++) {
    mpq_clear(&(bern_array[i]));
  }
  free(bern_array);
}


static unsigned long euler_array_size = 0;
static mp_int *euler_array;

static int bheuler(unsigned long limit)
{
  mp_int tmp;
  unsigned long j, k, N;
  int e;

  N = limit + 1;

  if (N < euler_array_size) {
    printf("Cache hit: %lu\n", N);
    return MP_OKAY;
  }

  /* For sake of simplicity */
  euler_array = malloc(sizeof(mp_int) * N + 2);
  if (euler_array == NULL) {
    return MP_MEM;
  }
  for (k = 0; k <= N; k++) {
    if ((e = mp_init(&euler_array[k])) != MP_OKAY) {
      return e;
    }
  }
  if ((e = mp_set_int(&euler_array[0], 1)) != MP_OKAY) {
    return e;
  }
  for (k = 1; k < N; k++) {
    /* euler_array[k] = (k)*euler_array[k-1] */
    if ((e = mp_mul_d(&euler_array[k - 1], (k), &euler_array[k])) != MP_OKAY) {
      return e;
    }
  }

  if ((e = mp_init(&tmp)) != MP_OKAY) {
    return e;
  }

  for (k = 1; k < N; k++) {
    for (j = k + 1; j < N; j++) {
      /* euler_array[j] =  (j-k)*euler_array[j-1]  +   (j-k+1)*euler_array[j] */
      /* tmp  =  (j-k)*euler_array[j-1]  */
      if ((e = mp_mul_d(&euler_array[j - 1], (j - k), &tmp)) != MP_OKAY) {
	return e;
      }
      /* euler_array[j] =   (j-k+1)*euler_array[j] */
      if ((e =
	   mp_mul_d(&euler_array[j], (j - k + 1),
		    &euler_array[j])) != MP_OKAY) {
	return e;
      }
      /* euler_array[j] =   euler_array[j]  + tmp */
      if ((e = mp_add(&euler_array[j], &tmp, &euler_array[j])) != MP_OKAY) {
	return e;
      }
    }
  }
  for (k = 0; k < N; k++) {
    /* Odd Euler numbers are negative */
    if (k & 0x1) {
      (euler_array[k]).sign = MP_NEG;
    }
  }
  euler_array_size = N;
  /* It is deemed good style to clean up after work */
  mp_clear(&tmp);
  return MP_OKAY;
}


int mp_euler_int(unsigned long n, mp_int * c)
{
  int e, k;

  /* all odd Euler numbers are zero */
  if ((n & 0x1) && n != 1) {
    mp_set_int(c, 0);
    return MP_OKAY;
  }
  if ((e = bheuler(n / 2)) != MP_OKAY) {
    return e;
  }
  k = n / 2;
  if ((e = mp_copy(&euler_array[k], c)) != MP_OKAY) {
    return e;
  }
  return MP_OKAY;
}

int mpq_euler(unsigned long n, mp_rat * c)
{
  int e;
  if ((e = mp_euler_int(n, &c->numerator)) != MP_OKAY) {
    return e;
  }
  return MP_OKAY;
}

void mpq_euler_free(void)
{
  unsigned long i = 0;
  for (; i < euler_array_size; i++) {
    mp_clear(&(euler_array[i]));
  }
  free(euler_array);
}


#ifndef BN_MP_SET_WORD_C
#define BN_MP_SET_WORD_C
#if (MP_PREC > 1)
int mp_set_word(mp_int * c, mp_word w)
{
  mp_zero(c);
  if (w == 0) {
    return MP_OKAY;
  }
  do {
    c->dp[c->used++] = (mp_digit) w & MP_MASK;
  } while ((w >>= DIGIT_BIT) > 0 && c->used < MP_PREC);
  if (w != 0) {
    return MP_VAL;
  }
  return MP_OKAY;
}
#else
#   warning "MP_PREC" must be at least 2 (two), better 3 (three)
#endif
#endif

static mp_rat h_temp;
mp_rat *_harmonics2(unsigned long a, unsigned long b)
{
  unsigned long m;
  mp_rat ta, tb;
  mp_int p, q, r, s;
  mp_word ps, qr;
  int e;

  if (b - a == 1) {
    if ((e = mpq_set_int(&h_temp, (long) 1, (long) a)) != MP_OKAY) {
      errornumber = e;
    }
    return &h_temp;
  }
  m = (a + b) >> 1;
  if ((e = mpq_init_multi(&ta, &tb, NULL)) != MP_OKAY) {
    errornumber = e;
  }
  if ((e = mp_init_multi(&p, &q, &r, &s, NULL)) != MP_OKAY) {
    errornumber = e;
  }

  mpq_exch(_harmonics2(a, m), &ta);
  mpq_exch(_harmonics2(m, b), &tb);

  mp_exch(&ta.numerator, &p);
  mp_exch(&ta.denominator, &q);
  mp_exch(&tb.numerator, &r);
  mp_exch(&tb.denominator, &s);

#ifdef BN_MP_SET_WORD_C
  if ((&p)->used == 1 && (&s)->used == 1) {
    ps = (&p)->dp[0] * (mp_word) (&s)->dp[0];
    if ((e = mp_set_word(&ta.numerator, ps)) != MP_OKAY) {
      errornumber = e;
    }
  } else {
    if ((e = mp_mul(&p, &s, &ta.numerator)) != MP_OKAY) {
      errornumber = e;
    }
  }
  if ((&q)->used == 1 && (&r)->used == 1) {
    qr = (&q)->dp[0] * (mp_word) (&r)->dp[0];
    if ((e = mp_set_word(&tb.numerator, qr)) != MP_OKAY) {
      errornumber = e;
    }

  } else {
    if ((e = mp_mul(&q, &r, &tb.numerator)) != MP_OKAY) {
      errornumber = e;
    }
  }
#else
  if ((e = mp_mul(&p, &s, &ta.numerator)) != MP_OKAY) {
    errornumber = e;
  }
  if ((e = mp_mul(&q, &r, &tb.numerator)) != MP_OKAY) {
    errornumber = e;
  }
#endif
  if ((e = mp_add(&ta.numerator, &tb.numerator, &h_temp.numerator)) != MP_OKAY) {
    errornumber = e;
  }

  if ((e = mp_mul(&q, &s, &h_temp.denominator)) != MP_OKAY) {
    errornumber = e;
  }

  mp_clear_multi(&p, &q, &r, &s, NULL);
  mpq_clear_multi(&ta, &tb, NULL);
  return &h_temp;
}

mp_rat *_harmonics1(unsigned long a, unsigned long b)
{
  unsigned long m;
  mp_rat ta, tb;
  int e;
  if (b - a == 1) {
    if ((e = mpq_set_int(&h_temp, (long) 1, (long) a)) != MP_OKAY) {
      errornumber = MP_VAL;
    }
    return &h_temp;
  }
  m = (a + b) >> 1;
  if ((e = mpq_init_multi(&ta, &tb, NULL)) != MP_OKAY) {
    errornumber = MP_VAL;
  }

  mpq_exch(_harmonics1(a, m), &ta);
  mpq_exch(_harmonics1(m, b), &tb);

  if ((e = mpq_add(&ta, &tb, &h_temp)) != MP_OKAY) {
    errornumber = MP_VAL;
  }
  mpq_clear_multi(&ta, &tb, NULL);
  return &h_temp;
}

int PARTIAL_HARMONICS_CUTOFF = 21000;
int mpq_harmonics(unsigned long n, mp_rat * c)
{
  int e;
  /* What to do with zero? */
  if(n == 0){
    return MP_OKAY;
  }
  if ((e = mpq_init(&h_temp)) != MP_OKAY) {
    return e;
  }
  if (n < (unsigned long)PARTIAL_HARMONICS_CUTOFF ) {
    mpq_exch(_harmonics2(1, n + 1), c);
    if ((e = mpq_reduce(c)) != MP_OKAY) {
      return e;
    }
  } else {
    mpq_exch(_harmonics1(1, n + 1), c);
  }
  mpq_clear(&h_temp);
  return 1;
}

