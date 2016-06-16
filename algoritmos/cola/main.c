#include "cola.h"
#include "testing.h"
#include <stdio.h>
#include <time.h>
/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

int main(void) {
  clock_t start = clock();
    /* Ejecuta todas las pruebas unitarias. */
    printf("~~~ PRUEBAS ALUMNO ~~~\n");
    pruebas_cola_alumno();
    double tiempo = clock() - start;
    printf ("el tiempo de ejecucion es : %f \n", tiempo * 1.00 / CLOCKS_PER_SEC);
    return failure_count() > 0;
}
