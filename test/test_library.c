#include "czrational.h"
int mp_get_str(const char *str, mp_int * a, int radix)
{
    return mp_read_radix(a, str, radix);
}

#ifndef MPI_LOG2
#   define MPI_LOG2 3.321928094887362347870319429489390175864831393024580612054756
#endif
int mp_put_str(mp_int * a, char **str, int radix)
{
    size_t buflen, multiplicator;
    mp_int tmp;
    mp_init(&tmp);
    multiplicator = (size_t) ((double) (a->used) / (double) (MPI_LOG2)) + 1;
    buflen =
	(multiplicator < (size_t) 4096) ? (size_t) 4096 : multiplicator + 100;
    *str = malloc(buflen);
    if (*str == NULL) {
	mp_clear(&tmp);
	return 0;
    }
    mp_copy(a, &tmp);
    mp_toradix(&tmp, *str, radix);
    mp_clear(&tmp);
    return MP_OKAY;
}

void mp_print(mp_int * a)
{
    char *buf;
    mp_put_str(a, &(buf), 10);
    printf("%s", buf);
    free(buf);
}
#include <time.h>
int main (int argc, char **argv){

    mp_int num1,den1,num2,den2;
    mp_rat q1,q2,q3,q4;
    //mp_rat *bernoulli;
    int i;
    clock_t start,stop;

    if (argc < 5) {
	fprintf(stderr, "usage: %s integer integer integer integer \n", argv[0]);
	exit(EXIT_FAILURE);
    }

    mp_init_multi(&num1,&den1,&num2,&den2,NULL);

    mp_get_str(argv[1], &num1, 10);
    mp_get_str(argv[2], &den1, 10);
    mp_get_str(argv[3], &num2, 10);
    mp_get_str(argv[4], &den2, 10);

    printf("Numerator   1: ");mp_print(&num1);puts("");
    printf("Denominator 1: ");mp_print(&den1);puts("");
    printf("Numerator   2: ");mp_print(&num2);puts("");
    printf("Denominator 2: ");mp_print(&den2);puts("");

    mpq_init_multi(&q1,&q2,&q3,&q4,NULL);puts("000");

    mpq_set(&q1,&num1,&den1);puts("111");
    printf("Rational1: ");mpq_print(&q1);puts("");
    mpq_set(&q2,&num2,&den2);puts("222");
    printf("Rational2: ");mpq_print(&q2);puts("");

    mpq_add(&q1,&q2,&q3);;
    printf("R1 + R2 = ");mpq_print(&q3);puts("");
    mpq_sub(&q1,&q2,&q3);
    printf("R1 - R2 = ");mpq_print(&q3);puts("");
    mpq_mul(&q1,&q2,&q3);
    printf("R1 * R2 = ");mpq_print(&q3);puts("");
    mpq_div(&q1,&q2,&q3);
    printf("R1 / R2 = ");mpq_print(&q3);puts("");
    //mpq_pow_d(&q1,123,&q3);
    printf("R1 ^ 123 = ");mpq_print(&q3);puts("");
    printf("cmp(R1, R2) = %d\n",mpq_cmp(&q1,&q2));
    printf("cmp(R2, R1) = %d\n",mpq_cmp(&q2,&q1));
    printf("cmp(R1, R1) = %d\n",mpq_cmp(&q1,&q1));
    mp_set_int(&num2,123);
    //mp_expt(&num1,&num2,&num1);
    printf("num1 ^123 = ");mp_fwrite(&num1,10,stdout);puts("");
    mpq_set_epsilon(50);
//mpq_set_int(&q1,128,2);
//mpq_set_int(&q1,529,1849);
//mpq_set_int(&q1,3481,11664);
//mpq_set_int(&q1,1764,1849);
mpq_set_int(&q1,44521,46656);
    mpq_sqrt(&q1,&q1);
    printf("sqrt(R1) = ");mpq_print(&q1);puts("");
    //SeidelBernoulli(20);
    //bernoulli = malloc(sizeof(mp_rat) * 102);
    start = clock();
    //bern_rat_init(10);
    //bhbern(50);
    stop = clock();
    puts("bernoulli");
    for(i=0;i<=(50);i++){
      //mpq_print(&bern_array[i]);printf("  %d\n",i);
    }
    mpq_bernoulli(10,&q1);
    printf("B_10 = ");mpq_print(&q1);puts("");
    mpq_bernoulli(4,&q1);
    printf("B_4 = ");mpq_print(&q1);puts("");
    mpq_bernoulli(0,&q1);
    printf("B_0 = ");mpq_print(&q1);puts("");
    mpq_bernoulli(1,&q1);
    printf("B_1 = ");mpq_print(&q1);puts("");
    mpq_bernoulli(2,&q1);
    printf("B_3 = ");mpq_print(&q1);puts("");
    mpq_bernoulli(100,&q1);
    printf("B_100 = ");mpq_print(&q1);puts("");
    mpq_bernoulli(98,&q1);
    printf("B_98 = ");mpq_print(&q1);puts("");
    printf("Time: %6.6f\n",( (double)stop - (double)start )/((double)CLOCKS_PER_SEC)  );
    mpq_bernoulli_free();
    exit(EXIT_SUCCESS);
}

