/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "calculadora.h"


void
calculadora_1(char *host)
{
	CLIENT *clnt;
	int  *result_1;
	entrada  sumar_1_arg;
	int  *result_2;
	entrada  restar_1_arg;
	int  *result_3;
	entrada  multiplicar_1_arg;
	double  *result_4;
	entrada  dividir_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, CALCULADORA, CALCULADORA_VER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	sumar_1_arg.arg1 = 5;
	sumar_1_arg.arg2 = 3;
	result_1 = sumar_1(&sumar_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	printf("\nEl resultado de sumar %i + %i es %i\n", sumar_1_arg.arg1, sumar_1_arg.arg2, *result_1);


	restar_1_arg.arg1 = 5;
	restar_1_arg.arg2 = 3;
	result_2 = restar_1(&restar_1_arg, clnt);
	if (result_2 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	printf("El resultado de restar %i - %i es %i\n", restar_1_arg.arg1, restar_1_arg.arg2, *result_2);


	multiplicar_1_arg.arg1 = 5;
	multiplicar_1_arg.arg2 = 3;
	result_3 = multiplicar_1(&multiplicar_1_arg, clnt);
	if (result_3 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	printf("El resultado de multiplicar %i * %i es %i\n", multiplicar_1_arg.arg1, multiplicar_1_arg.arg2, *result_3);


	dividir_1_arg.arg3 = 5;
	dividir_1_arg.arg4 = 3;
	result_4 = dividir_1(&dividir_1_arg, clnt);
	if (result_4 == (double *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	printf("El resultado de dividir %f / %f es %f\n", dividir_1_arg.arg3, dividir_1_arg.arg4, *result_4);

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	calculadora_1 (host);
exit (0);
}
