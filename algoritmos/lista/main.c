#include "testing.h"
#include <stdio.h>
#include <time.h>
void pruebas_lista_alumno(void);

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

int main(void) {
  clock_t inicio = clock();
  /* Ejecuta todas las pruebas unitarias. */
  printf("~~~ PRUEBAS DEL ALUMNO ~~~\n");
  pruebas_lista_alumno();
  double tiempo  = clock() - inicio;
  printf("el tiempo de ejecucion fue : %f \n", tiempo * 1.00 / CLOCKS_PER_SEC);
  return failure_count() > 0;
}
