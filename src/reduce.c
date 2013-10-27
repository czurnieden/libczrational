#include "czrational.h"
int mpq_reduce(mp_rat * a)
{
    mp_int gcd;
    int e, sgn = mpq_get_sign(a);

    /* check if num is zero -> return 0 if it is */
    if (mp_iszero(&a->numerator)) {
	mp_set_int(&a->numerator, 0);
	mp_set_int(&a->denominator, 1);
	mpq_set_sign(a, MP_ZPOS);
	return MP_OKAY;
    }
    /* check if den is 1 -> return if it is */
    if (mp_isone(&a->denominator)) {
	return MP_OKAY;
    }
    /* check if den is zero -> return undefined if it is */
    if (mp_iszero(&a->denominator)) {
	mp_set_int(&a->numerator, 0);
	mp_set_int(&a->denominator, 0);
	a->sign = MP_ZPOS;
	return MPQ_DIVISION_BY_ZERO;
    }
    /* check if den = num -> return 1 */
    if (mpq_isone(a)) {
	mp_set_int(&a->numerator, 1);
	mp_set_int(&a->denominator, 1);
	return MP_OKAY;
    }
    mp_init(&gcd);

    /* compute gcd(num,den) */
    if ((e = mp_gcd(&a->numerator, &a->denominator, &gcd)) != MP_OKAY) {
	return e;
    }
    if (mp_isone(&gcd)) {
	/* nothing to do */
	return MP_OKAY;
    }
    /* set num to num/gcd */
    if ((e = mp_div(&a->numerator, &gcd, &a->numerator, NULL)) != MP_OKAY) {
	return e;
    }
    /* set den to den/gcd */
    if ((e = mp_div(&a->denominator, &gcd, &a->denominator, NULL)) != MP_OKAY) {
	return e;
    }
    /* not to forget: */
    (&a->numerator)->sign = MP_ZPOS;
    (&a->denominator)->sign = MP_ZPOS;
    a->sign = sgn;
    return MP_OKAY;
}
