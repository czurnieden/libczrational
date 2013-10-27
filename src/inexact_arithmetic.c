#include "czrational.h"

static int mpq_epsilon;
void mpq_set_epsilon(int eps)
{

    if (eps <= 0) {
	mpq_epsilon = 0;
    } else {
	/* eps assumed to be precision in number of decimal digits */
	mpq_epsilon =
	    (int) ((double) eps * MPI_LOG2) + (int) log2((double) eps);
    }
}

int mpq_get_epsilon(void)
{
    return mpq_epsilon;
}

/* sqrt() meant as a test for epsilon */
int mpq_sqrt(mp_rat * a, mp_rat * c)
{
    int e;
    if (mpq_isneg(a)) {
	return MP_VAL;
    }
    if ((e = mpq_copy(a, c)) != MP_OKAY) {
	return e;
    }
    //printf("epsilon = %d\n",mpq_get_epsilon());
    /*
     * This is too brutal.
     * There are better ways to do it.
     */
    int eps = mpq_get_epsilon();
    if ((eps & 0x1)) {
	eps++;
    }
    if ((e = mp_mul_2d(&c->numerator, eps << 1, &c->numerator)) != MP_OKAY) {
	return e;
    }

    if ((e = mp_mul_2d(&c->denominator, eps << 1, &c->denominator)) != MP_OKAY) {
	return e;
    }


    /*
     * mp_int tenpow;
     * mp_init(&tenpow);
     * mp_set_int(&tenpow,10);
     * mp_expt_d(&tenpow,eps,&tenpow);
     * mp_mul(&c->numerator, &tenpow ,&c->numerator);
     * mp_mul(&c->denominator,&tenpow,&c->denominator);
     */
    if ((e = mp_sqrt(&c->numerator, &c->numerator)) != MP_OKAY) {
	return e;
    }

    if ((e = mp_sqrt(&c->denominator, &c->denominator)) != MP_OKAY) {
	return e;
    }

    if ((e = mpq_reduce(c)) != MP_OKAY) {
	return e;
    }
    //mp_clear(&tenpow);
    return MP_OKAY;
}
