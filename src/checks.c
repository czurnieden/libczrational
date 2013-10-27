#include "czrational.h"
#include <stdarg.h>


int mpq_iszero(mp_rat * a)
{
    if (mp_iszero(&a->numerator)
	&& mp_isone(&a->denominator)) {
	return MP_YES;
    }
    return MP_NO;
}

/* does not check for sign! */
int mpq_isone(mp_rat * a)
{
    if (mp_cmp(&a->numerator, &a->denominator) == MP_EQ) {
	return MP_YES;
    }
    return MP_NO;
}

int mpq_isinteger(mp_rat * a)
{
    if (mp_isone(&a->denominator)) {
	return MP_YES;
    }
    return MP_NO;
}

int mpq_isundefined(mp_rat * a)
{
    if (mp_iszero(&a->numerator)
	&& mp_iszero(&a->denominator)) {
	return MP_YES;
    }
    return MP_NO;
}


/*

  This is a computationally expensive function.

  returns
    MP_EQ if equal
    MP_LT if a > b
    MP_GT if a < b
*/
int mpq_cmp(mp_rat * a, mp_rat * b)
{
    mp_int p1, p2;
    int e, wnuma, wdena, wnumb, wdenb, s1, s2;

    /* a == b, actually the very same number */
    if (a == b) {
	return MP_EQ;
    }
    /* a < b */
    if (a->sign == MP_NEG && b->sign == MP_ZPOS) {
	return MP_LT;
    }
    /* a > b */
    if (a->sign == MP_ZPOS && b->sign == MP_NEG) {
	return MP_GT;
    }
    /* some more shortcuts */
    if (mpq_iszero(a)) {
	/* a == b (both zero) */
	if (mpq_iszero(b)) {
	    return MP_EQ;
	}
	/* a < b */
	if (b->sign == MP_ZPOS) {
	    return MP_LT;
	}
	/* a > b */
	return MP_GT;
    }
    if (mpq_iszero(b)) {
	/* a > b */
	if (a->sign == MP_ZPOS) {
	    return MP_GT;
	}
	/* a < b */
	return MP_LT;
    }

    if (mpq_isinteger(a) && mpq_isinteger(b)) {
	return mp_cmp(&a->numerator, &b->numerator);
    }

    /*
     * We can use a rough approximation of the result because we are only
     * interessted in the magnitudes.
     */
    wnuma = (&a->numerator)->used;
    wdena = (&a->denominator)->used;
    wnumb = (&b->numerator)->used;
    wdenb = (&b->denominator)->used;
    s1 = wnuma + wdenb;
    s2 = wnumb + wdena;
    if (s1 < s2 - 1) {
	return ((a->sign == MP_NEG) ? MP_ZPOS : MP_NEG);
    }
    if (s2 < s1 - 1) {
	return ((a->sign == MP_NEG) ? MP_NEG : MP_ZPOS);
    }
    /* This is gonna be brutal, so don't use cmp() frivolously! */
    mp_init_multi(&p1, &p2, NULL);
    if ((e = mp_mul(&a->numerator, &b->denominator, &p1)) != MP_OKAY) {
	return e;
    }
    if ((e = mp_mul(&b->numerator, &a->denominator, &p2)) != MP_OKAY) {
	mp_clear(&p2);
	return e;
    }

    e = mp_cmp(&p1, &p2);
    mp_clear_multi(&p1, &p2, NULL);
    if (a->sign == MP_NEG) {
	return ((e == MP_ZPOS) ? MP_NEG : MP_ZPOS);
    }
    return e;
}

int mpq_isneg(mp_rat * a)
{
    return ((a->sign == MP_NEG) ? MP_YES : MP_NO);
}
