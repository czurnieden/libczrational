#include "czrational.h"

void mpq_normalize_sign(mp_rat * a)
{
    int sign_n, sign_d;

    sign_n = a->numerator.sign;
    sign_d = a->denominator.sign;
    a->sign = (sign_n != sign_d) ? MP_NEG : MP_ZPOS;
    a->numerator.sign = MP_ZPOS;
    a->denominator.sign = MP_ZPOS;
}

/* returns sign of mp_rat a */
int mpq_get_sign(mp_rat * a)
{
    return a->sign;
}

/* sets sign of mp_rat a to sign given in "sign", returns old sign */
int mpq_set_sign(mp_rat * a, int sign)
{
    int sgn;
    sgn = a->sign;
    a->sign = (sign < 0 || sign == MP_NEG) ? MP_NEG : MP_ZPOS;
    a->numerator.sign = MP_ZPOS;
    a->denominator.sign = MP_ZPOS;
    return sgn;
}

/* reverses sign of mp_rat a */
int mpq_neg(mp_rat * a)
{
    int sgn;
    if (mp_iszero(&a->numerator)) {
	mpq_set_sign(a, MP_ZPOS);
	return MP_OKAY;
    }
    sgn = mpq_get_sign(a);
    sgn = (sgn == MP_NEG) ? MP_ZPOS : MP_NEG;
    a->numerator.sign = MP_ZPOS;
    a->denominator.sign = MP_ZPOS;
    return mpq_set_sign(a, sgn);
}
