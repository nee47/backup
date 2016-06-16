
#include "pila.h"
#include "testing.h"
#include <stdio.h>
#include <time.h>
/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

int main(void)
{
  clock_t start = clock();
    /* Ejecuta todas las pruebas unitarias. */
    printf("~~~ PRUEBAS ALUMNO ~~~\n");
    pruebas_pila_alumno();
    double tiempo = clock() - start;
    printf("el tiempo de ejecucion fue : %f \n", tiempo * 1.00 / CLOCKS_PER_SEC);
    return failure_count() > 0;
}
