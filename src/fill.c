#include "czrational.h"
#include <stdarg.h>


/* sets given mp_int b as the numerator in mp_rat a */
int mpq_set_num(mp_rat * a, mp_int * b)
{
    int e;

    if ((e = mp_copy(b, &a->numerator)) != MP_OKAY) {
	return e;
    }
    mpq_normalize_sign(a);
    if ((e = mpq_reduce(a)) != MP_OKAY) {
	return e;
    }
    return MP_OKAY;
}

/* sets given mp_int b as the denominator in mp_rat a */
int mpq_set_den(mp_rat * a, mp_int * b)
{
    int e;

    if ((e = mp_copy(b, &a->denominator)) != MP_OKAY) {
	return e;
    }
    mpq_normalize_sign(a);
    if ((e = mpq_reduce(a)) != MP_OKAY) {
	return e;
    }
    return MP_OKAY;
}


/* sets given mp_int p,q as the numerator,denominator in mp_rat a */
int mpq_set(mp_rat * a, mp_int * p, mp_int * q)
{
    int e;

    if ((e = mp_copy(p, &a->numerator)) != MP_OKAY) {
	return e;
    }
    if ((e = mp_copy(q, &a->denominator)) != MP_OKAY) {
	return e;
    }
    mpq_normalize_sign(a);
    if ((e = mpq_reduce(a)) != MP_OKAY) {
	return e;
    }
    return MP_OKAY;
}


/* sets given unsigned long b as the numerator in mp_rat a */
int mpq_set_num_int(mp_rat * a, long b)
{
    int e;

    if ((e = mp_set_int(&a->numerator, labs(b))) != MP_OKAY) {
	return e;
    }
    if (b < 0) {
	mpq_set_sign(a, MP_NEG);
    }
    if ((e = mpq_reduce(a)) != MP_OKAY) {
	return e;
    }
    return MP_OKAY;
}

/* sets given unsigned long b as the denominator in mp_rat a */
int mpq_set_den_int(mp_rat * a, long b)
{
    int e;

    if ((e = mp_set_int(&a->denominator, labs(b))) != MP_OKAY) {
	return e;
    }
    if (b < 0) {
	mpq_set_sign(a, MP_NEG);
    }
    if ((e = mpq_reduce(a)) != MP_OKAY) {
	return e;
    }
    return MP_OKAY;
}


/* sets given unsigned longs p,q as the numerator,denominator in mp_rat a */
int mpq_set_int(mp_rat * a, long p, long q)
{
    int e;

    if ((e = mp_set_int(&a->numerator, labs(p))) != MP_OKAY) {
	return e;
    }
    if ((e = mp_set_int(&a->denominator, labs(q))) != MP_OKAY) {
	return e;
    }
    if ((p * q) < 0) {
	mpq_set_sign(a, MP_NEG);
    }
    if ((e = mpq_reduce(a)) != MP_OKAY) {
	return e;
    }
    return MP_OKAY;
}
