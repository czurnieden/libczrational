#include "czrational.h"
#include <stdarg.h>

int mpq_copy(mp_rat * a, mp_rat * b)
{
    int e;
    if ((e = mp_copy(&a->numerator, &b->numerator)) != MP_OKAY) {
	return e;
    }
    if ((e = mp_copy(&a->denominator, &b->denominator)) != MP_OKAY) {
	return e;
    }
    b->sign = a->sign;
    return MP_OKAY;
}

void mpq_exch(mp_rat * a, mp_rat * b)
{
    mp_exch(&a->numerator, &b->numerator);
    mp_exch(&a->denominator, &b->denominator);
}
