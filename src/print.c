#include "czrational.h"
#include <stdarg.h>

void mpq_print(mp_rat * a)
{
    printf("%c", (a->sign == MP_ZPOS) ? '+' : '-');
    mp_fwrite(&a->numerator, 10, stdout);
    putchar('/');
    mp_fwrite(&a->denominator, 10, stdout);
}

void mpq_fprint(mp_rat * a, FILE * stream)
{
    printf("%c", (a->sign == MP_ZPOS) ? '+' : '-');
    mp_fwrite(&a->numerator, 10, stream);
    putchar('/');
    mp_fwrite(&a->denominator, 10, stream);
}

void mpq_fwrite(mp_rat * a, int radix, FILE * stream)
{
    printf("%c", (a->sign == MP_ZPOS) ? '+' : '-');
    mp_fwrite(&a->numerator, radix, stream);
    putchar('/');
    mp_fwrite(&a->denominator, radix, stream);
}
