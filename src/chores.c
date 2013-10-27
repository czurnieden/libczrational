#include "czrational.h"
#include <stdarg.h>

int mpq_init(mp_rat * a)
{
    int e;

    if ((e = mp_init_multi(&a->numerator, &a->denominator, NULL)) != MP_OKAY) {
	return e;
    }
    a->sign = MP_ZPOS;
    return MP_OKAY;
}

void mpq_clear(mp_rat * a)
{
    mp_clear_multi(&a->numerator, &a->denominator, NULL);
    a->sign = MP_ZPOS;
}

void mpq_clear_multi(mp_rat * mp, ...)
{
    mp_rat *next_mp = mp;
    va_list args;
    va_start(args, mp);
    while (next_mp != NULL) {
	mpq_clear(next_mp);
	next_mp = va_arg(args, mp_rat *);
    }
    va_end(args);
}

/* Shamelessly stolen, as it is, from libtommath */
int mpq_init_multi(mp_rat * mp, ...)
{
    mp_err res = MP_OKAY;	/* Assume ok until proven otherwise */
    int n = 0;			/* Number of ok inits */
    mp_rat *cur_arg = mp;
    va_list args;

    va_start(args, mp);		/* init args to next argument from caller */
    while (cur_arg != NULL) {
	if (mpq_init(cur_arg) != MP_OKAY) {
	    /* Oops - error! Back-track and mp_clear what we already
	     * succeeded in init-ing, then return error.
	     */
	    va_list clean_args;

	    /* end the current list */
	    va_end(args);

	    /* now start cleaning up */
	    cur_arg = mp;
	    va_start(clean_args, mp);
	    while (n--) {
		mpq_clear(cur_arg);
		cur_arg = va_arg(clean_args, mp_rat *);
	    }
	    va_end(clean_args);
	    res = MP_MEM;
	    break;
	}
	n++;
	cur_arg = va_arg(args, mp_rat *);
    }
    va_end(args);
    return res;			/* Assumed ok, if error flagged above. */
}
