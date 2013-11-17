#include "czrational.h"
#include <stdarg.h>

int mpq_inverse(mp_rat * a)
{
    int e;
    if (mp_iszero(&a->numerator)) {
	/* not yet but in the future */
	return MPQ_DIVISION_BY_ZERO;
    }
    if (mp_iszero(&a->denominator)) {
	if ((e = mpq_set_int(a, 0, 1)) != MP_OKAY) {
	    return e;
	}
	a->sign = MP_ZPOS;
	return MP_OKAY;
    }
    mp_exch(&a->numerator, &a->denominator);
    return MP_OKAY;
}

int mpq_add(mp_rat * a, mp_rat * b, mp_rat * c)
{
    int e;
    mp_int lcm, tmp1, tmp2, tmp3, tmp4;
    if (mp_iszero(&a->numerator)) {
	if ((e = mpq_copy(b, c)) != MP_OKAY) {
	    return e;
	}
	return MP_OKAY;
    }
    if (mp_iszero(&b->numerator)) {
	if ((e = mpq_copy(a, c)) != MP_OKAY) {
	    return e;
	}
	return MP_OKAY;
    }
    /* let libtommath take care of the signs */
    (&a->numerator)->sign = a->sign;
    (&b->numerator)->sign = b->sign;
    if (mpq_isinteger(a)== MP_YES && mpq_isinteger(b) == MP_YES) {
	if ((e =
	     mp_add(&a->numerator, &b->numerator, &c->numerator)) != MP_OKAY) {
	    return e;
	}
	c->sign = (&c->numerator)->sign;
	(&a->numerator)->sign = MP_ZPOS;
	(&b->numerator)->sign = MP_ZPOS;
	(&c->numerator)->sign = MP_ZPOS;
	(&c->denominator)->sign = MP_ZPOS;
	if ((e = mp_set_int(&c->denominator, 1)) != MP_OKAY) {
	    return e;
	}
	return MP_OKAY;
    }
    // a + b/c = (a*c +b)/c
    if(mpq_isinteger(a)== MP_YES && mpq_isinteger(b) == MP_NO ){
   	if ((e =
	     mp_mul(&a->numerator, &b->denominator, &c->numerator)) != MP_OKAY) {
	    return e;
	}
        if ((e =
	     mp_add(&b->numerator, &c->numerator, &c->numerator)) != MP_OKAY) {
	    return e;
	}
        mp_copy(&b->denominator,&c->denominator);
        goto end_add;
    }
    // a/c + b = (a +b*c)/c
    if(mpq_isinteger(a) == MP_NO && mpq_isinteger(b)== MP_YES ){
   	if ((e =
	     mp_mul(&b->numerator, &a->denominator, &c->numerator)) != MP_OKAY) {
	    return e;
	}
        if ((e =
	     mp_add(&a->numerator, &c->numerator, &c->numerator)) != MP_OKAY) {
	    return e;
	}
        mp_copy(&a->denominator,&c->denominator);
        goto end_add;
    }

    mp_init_multi(&lcm, &tmp1, &tmp2, &tmp3, &tmp4, NULL);
    /* lcm(a,b) */
    if ((e = mp_lcm(&a->denominator, &b->denominator, &lcm)) != MP_OKAY) {
	return e;
    }
    if ((e = mp_div(&lcm, &a->denominator, &tmp1, NULL)) != MP_OKAY) {
	return e;
    }
    if ((e = mp_mul(&tmp1, &a->numerator, &tmp2)) != MP_OKAY) {
	return e;
    }
    if ((e = mp_div(&lcm, &b->denominator, &tmp3, NULL)) != MP_OKAY) {
	return e;
    }
    if ((e = mp_mul(&tmp3, &b->numerator, &tmp4)) != MP_OKAY) {
	return e;
    }
    if ((e = mp_add(&tmp2, &tmp4, &c->numerator)) != MP_OKAY) {
	return e;
    }
    if ((e = mp_copy(&lcm, &c->denominator)) != MP_OKAY) {
	return e;
    }
    mp_clear_multi(&lcm, &tmp1, &tmp2, &tmp3, &tmp4, NULL);
end_add:
    c->sign = (&c->numerator)->sign;
    (&a->numerator)->sign = MP_ZPOS;
    (&b->numerator)->sign = MP_ZPOS;
    (&c->numerator)->sign = MP_ZPOS;
    if ((e = mpq_reduce(c)) != MP_OKAY) {
	return e;
    }

    return MP_OKAY;
}

int mpq_sub(mp_rat * a, mp_rat * b, mp_rat * c)
{
    int e;
    mp_int lcm, tmp1, tmp2, tmp3, tmp4;
    if (mp_iszero(&a->numerator)) {
	mpq_neg(b);
	if ((e = mpq_copy(b, c)) != MP_OKAY) {
	    return e;
	}
	mpq_set_sign(c, MP_NEG);
	return MP_OKAY;
    }
    if (mp_iszero(&b->numerator)) {
	if ((e = mpq_copy(a, c)) != MP_OKAY) {
	    return e;
	}
	return MP_OKAY;
    }

    if (mpq_isinteger(a) == MP_YES && mpq_isinteger(b) == MP_YES) {
	(&a->numerator)->sign = a->sign;
	(&b->numerator)->sign = b->sign;
	if ((e =
	     mp_sub(&a->numerator, &b->numerator, &c->numerator)) != MP_OKAY) {
	    return e;
	}
	c->sign = (&c->numerator)->sign;
	(&c->numerator)->sign = MP_ZPOS;
	if ((e = mp_set_int(&c->denominator, 1)) != MP_OKAY) {
	    return e;
	}
	return MP_OKAY;
    }

    // a - b/c = (a*c - b)/c
    if(mpq_isinteger(a)== MP_YES && mpq_isinteger(b) == MP_NO ){
   	if ((e =
	     mp_mul(&a->numerator, &b->denominator, &c->numerator)) != MP_OKAY) {
	    return e;
	}
        if ((e =
	     mp_sub(&c->numerator, &b->numerator, &c->numerator)) != MP_OKAY) {
	    return e;
	}
        mp_copy(&b->denominator,&c->denominator);
        goto end_sub;
    }
    // a/c - b = (a - b*c)/c
    if(mpq_isinteger(a) == MP_NO && mpq_isinteger(b)== MP_YES ){
   	if ((e =
	     mp_mul(&b->numerator, &a->denominator, &c->numerator)) != MP_OKAY) {
	    return e;
	}
        if ((e =
	     mp_sub(&a->numerator, &c->numerator, &c->numerator)) != MP_OKAY) {
	    return e;
	}
        mp_copy(&a->denominator,&c->denominator);
        goto end_sub;
    }

    /* let libtommath take care of the signs */
    (&a->numerator)->sign = a->sign;
    (&b->numerator)->sign = b->sign;
    mp_init_multi(&lcm, &tmp1, &tmp2, &tmp3, &tmp4, NULL);
    /* lcm(a,b) */
    if ((e = mp_lcm(&a->denominator, &b->denominator, &lcm)) != MP_OKAY) {
	return e;
    }
    if ((e = mp_div(&lcm, &a->denominator, &tmp1, NULL)) != MP_OKAY) {
	return e;
    }
    if ((e = mp_mul(&tmp1, &a->numerator, &tmp2)) != MP_OKAY) {
	return e;
    }
    if ((e = mp_div(&lcm, &b->denominator, &tmp3, NULL)) != MP_OKAY) {
	return e;
    }
    if ((e = mp_mul(&tmp3, &b->numerator, &tmp4)) != MP_OKAY) {
	return e;
    }
    if ((e = mp_sub(&tmp2, &tmp4, &c->numerator)) != MP_OKAY) {
	return e;
    }
    if ((e = mp_copy(&lcm, &c->denominator)) != MP_OKAY) {
	return e;
    }
    mp_clear_multi(&lcm, &tmp1, &tmp2, &tmp3, &tmp4, NULL);
end_sub:
    c->sign = (&c->numerator)->sign;
    (&a->numerator)->sign = MP_ZPOS;
    (&b->numerator)->sign = MP_ZPOS;
    (&c->numerator)->sign = MP_ZPOS;
    if ((e = mpq_reduce(c)) != MP_OKAY) {
	return e;
    }
    return MP_OKAY;
}


int mpq_mul(mp_rat * a, mp_rat * b, mp_rat * c)
{
    int e;
    if (mp_iszero(&a->numerator) || mp_iszero(&b->numerator)) {
	if ((e = mpq_set_int(c, 0, 1)) != MP_OKAY) {
	    return e;
	}
	c->sign = MP_ZPOS;
	return MP_OKAY;
    }

    if ((e = mp_mul(&a->numerator, &b->numerator, &c->numerator)) != MP_OKAY) {
	return e;
    }
    if ((e =
	 mp_mul(&a->denominator, &b->denominator,
		&c->denominator)) != MP_OKAY) {
	return e;
    }
    if ((e = mpq_reduce(c)) != MP_OKAY) {
	return e;
    }
    c->sign = (a->sign != b->sign) ? MP_NEG : MP_ZPOS;
    return MP_OKAY;
}

int mpq_div(mp_rat * a, mp_rat * b, mp_rat * c)
{
    int e;
    if (mp_iszero(&a->numerator)) {
	if ((e = mpq_set_int(c, 0, 1)) != MP_OKAY) {
	    return e;
	}
	return MP_OKAY;
    }
    if (mp_iszero(&b->numerator)) {
	return MPQ_DIVISION_BY_ZERO;
    }
    if ((e = mpq_inverse(b)) != MP_OKAY) {
	return e;
    }
    if ((e = mpq_mul(a, b, c)) != MP_OKAY) {
	return e;
    }
    if ((e = mpq_inverse(b)) != MP_OKAY) {
	return e;
    }
    if ((e = mpq_reduce(c)) != MP_OKAY) {
	return e;
    }
    c->sign = (a->sign != b->sign) ? MP_NEG : MP_ZPOS;
    return MP_OKAY;
}


int mpq_pow_d(mp_rat * a, long d, mp_rat * c)
{
    int e;
    long abs_d;
    mp_int temp;

    /* 0^x = 0; x!=0 */
    if (mpq_iszero(a)) {
	if (d == 0) {
	    if ((e = mpq_set_int(c, 0, 0)) != MP_OKAY) {
		return e;
	    }
	    return MPQ_DIVISION_BY_ZERO;
	}
	if ((e = mpq_set_int(c, 0, 1)) != MP_OKAY) {
	    return e;
	}
	return MP_OKAY;
    }
    /* 1^ x = 1 */
    if (mpq_isone(a)) {
	/* mpq_set_* ignore signs. Behaviour may change in the future */
	if ((e = mpq_set_int(c, 1, 1)) != MP_OKAY) {
	    return e;
	}
	/* (-1)^x = 1 if x is even, -1 otherwise */
	if (mpq_isneg(a) && labs(d) & 0x1) {
	    c->sign = MP_NEG;
	}
	return MP_OKAY;
    }


    /* x^0 = 1 ; x != 0 */
    if (d == 0) {
	if (mpq_iszero(a)) {
	    if ((e = mpq_set_int(c, 0, 0)) != MP_OKAY) {
		return e;
	    }
	    return MPQ_DIVISION_BY_ZERO;
	}
	if ((e = mpq_set_int(c, 1, 1)) != MP_OKAY) {
	    return e;
	}
	c->sign = MP_ZPOS;
	return MP_OKAY;
    }

    abs_d = labs(d);
    /* it is mp_expt_d (mp_int * a, mp_digit b, mp_int * c), hence the limit */
    if (abs_d < DIGIT_SIZE) {
	if ((e = mp_expt_d(&a->numerator, abs_d, &c->numerator)) != MP_OKAY) {
	    return e;
	}
	if ((e = mp_expt_d(&a->denominator, abs_d, &c->denominator)) != MP_OKAY) {
	    return e;
	}
    } else {
	mp_init(&temp);
	if ((e = mp_set_int(&temp, (unsigned long) abs_d)) != MP_OKAY) {
	    return e;
	}
	/* There is no function mp_expt()? Oh my ... */
	if ((e = mp_expt(&a->numerator, &temp, &c->numerator)) != MP_OKAY) {
	    return e;
	}
	if ((e = mp_expt(&a->denominator, &temp, &c->denominator)) != MP_OKAY) {
	    return e;
	}
    }
    /* (p/q)^x = (p^x)/(q^x) with integer x and x > 0, (q^x)/(p^x) with x < 0 */
    if (d < 0) {
	mp_exch(&c->numerator, &c->denominator);
    }
    /* set sign according to rule described above */
    if (mpq_isneg(a) && labs(d) & 0x1) {
	c->sign = MP_NEG;
    }
    return MP_OKAY;
}

int mpq_pow(mp_rat * a, mp_int * d, mp_rat * c)
{
    int e;
    mp_int temp;

    /* 0^x = 0; x!=0 */
    if (mpq_iszero(a)) {
	if (d == 0) {
	    if ((e = mpq_set_int(c, 0, 0)) != MP_OKAY) {
		return e;
	    }
	    return MPQ_DIVISION_BY_ZERO;
	}
	if ((e = mpq_set_int(c, 0, 1)) != MP_OKAY) {
	    return e;
	}
	return MP_OKAY;
    }
    /* 1^ x = 1 */
    if (mpq_isone(a)) {

	if ((e = mpq_set_int(c, 1, 1)) != MP_OKAY) {
	    return e;
	}
	/* (-1)^x = 1 if x is even, -1 otherwise */
	if (mpq_isneg(a) && mp_isodd(d)) {
	    c->sign = MP_NEG;
	}
	return MP_OKAY;
    }
    /* x^0 = 1 ; x != 0 */
    if (mp_iszero(d)) {
	if (mpq_iszero(a)) {
	    if ((e = mpq_set_int(c, 0, 0)) != MP_OKAY) {
		return e;
	    }
	    return MPQ_DIVISION_BY_ZERO;
	}
	if ((e = mpq_set_int(c, 1, 1)) != MP_OKAY) {
	    return e;
	}
	c->sign = MP_ZPOS;
	return MP_OKAY;
    }

    if ((e = mp_expt(&a->numerator, &temp, &c->numerator)) != MP_OKAY) {
	return e;
    }
    if ((e = mp_expt(&a->denominator, &temp, &c->denominator)) != MP_OKAY) {
	return e;
    }
    if (d->sign == MP_NEG) {
	mp_exch(&c->numerator, &c->denominator);
    }
    if (mpq_isneg(a) && mp_isodd(d)) {
	c->sign = MP_NEG;
    }
    return MP_OKAY;
}

int mpq_sqr(mp_rat * a, mp_rat * c)
{
  int e;
  if ((e = mp_sqr(&a->numerator, &c->numerator)) != MP_OKAY) {
    return e;
  }
  if ((e = mp_sqr(&a->denominator, &c->denominator)) != MP_OKAY) {
    return e;
  }
  c->sign = MP_ZPOS;
  /*
  if ((e = mpq_reduce(c)) != MP_OKAY) {
    return e;
  }
  */
  return MP_OKAY;
}
