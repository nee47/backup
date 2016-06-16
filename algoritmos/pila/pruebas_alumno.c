#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define TAM_VOL 60000
/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
typedef struct tipo{
	void* dato;
} tipo_t;



void pruebas_pila_vacia(){
  printf("   -PRUEBA PILA VACIA-   \n");
  pila_t* pila =pila_crear();
  print_test("Pila esta vacia devuelve true ", pila_esta_vacia(pila));
  print_test("pila ver tope devuelve NULL", !pila_ver_tope(pila));
  print_test("pila desapilar devuelve NULL", !pila_desapilar(pila));
  pila_destruir(pila);
  print_test("*** *pila destruida ***** ",true);
}

void pruebas_apilar_desapilar_elementos(){
  printf("\n pruebas apilar desapilar elementos **** \n");
  pila_t* pila=pila_crear();
  int a=5, b=9, c=20;
  print_test("pila esta vacia devuelv true", pila_esta_vacia(pila));
  print_test("pila apilar el 5 devuelve true", pila_apilar(pila, &a));
  print_test("pila no esta vacia devuelve true", !pila_esta_vacia(pila));
  print_test("pila ver tope devuelve 5",*(int*)pila_ver_tope(pila) == a);
  print_test("pila apilar el 9 devuelve true", pila_apilar(pila,&b));
  print_test("pila ver tope devuelve 9", *(int*)pila_ver_tope(pila)== b);
  print_test("pila apilar el 20 devuelve true", pila_apilar(pila, &c));
  print_test("pila ver tope devuelve 20", *(int*)pila_ver_tope(pila)== c);
  print_test("pila desapilar devuvelve 20", *(int*)pila_desapilar(pila) == c);
  print_test("pila desapilar devuelve 9", *(int*)pila_desapilar(pila)==b);
  print_test("pila desapilar devuelve 5", *(int*)pila_desapilar(pila)== a);
  print_test("pila desapilar devuelve NULL (ya no hay elementos)", !pila_desapilar(pila));
  print_test("pila esta vacia despues de desapialr todo", pila_esta_vacia(pila));
  pila_destruir(pila);
  print_test("***** LA PILA FUE DESTRUIDA **** ",true);
}



void prueba_destruir_elementos(){
  printf("\n  PRUEBA DESTRUIR PILA CON ELEMENTOS \n");
  char cadena1[] = "cuchara";
  char cadena2[] = "tenedor";
  char cadena3[] = "cuchillo";

  pila_t* pila = pila_crear();
  print_test("Pila esta vacia", pila_esta_vacia(pila));
  print_test("apilo cadena1 -cuchara-", pila_apilar(pila, cadena1));
  print_test("pila ver tope devuelve cuchara", pila_ver_tope(pila) == cadena1);
  print_test("apilo cadena2 -tenedor-", pila_apilar(pila, cadena2));
  print_test("pila ver tope devuelve tenedor", pila_ver_tope(pila) == cadena2);
  print_test("apilo cadena3 -cuchillo-", pila_apilar(pila, cadena3));
  print_test("pila ver tope devuelve cuchillo ", pila_ver_tope(pila)==cadena3);
  pila_destruir(pila);
  print_test("**** pila destruida *****", true);

}


void pruebas_volumen(){
  printf("\n -PRUEBAS VOLUMEN- \n");
  bool ok = true ;
  int vec[TAM_VOL];
  pila_t* pila = pila_crear();

  for(int a=0; a < TAM_VOL; a++ ){
    vec[a] = a;
    ok = pila_apilar(pila, &vec[a]);
    if (!ok) break ;
    ok = *(int*)pila_ver_tope(pila) == vec[a] ? true : false;
    if (!ok) break ;
  }

  print_test("Todos los elemetos fueron apilados", ok);

  for( int b = 1  ; b < TAM_VOL + 1; b++){
    ok = *(int*)pila_desapilar(pila) == vec[TAM_VOL - b] ? true : false; 
    if (!ok) break;
  }

  print_test("Todos los elementos fueron desapilados en orden", ok);
  print_test("pila esta vacia ", pila_esta_vacia(pila));
  pila_destruir(pila);
}


void prueba_estructuras(){
	printf("\n **** INICIO DE PRUEBAS CON STRUCT **** \n");
	pila_t* pila8=pila_crear();
	tipo_t* temp=malloc(sizeof(tipo_t));
	print_test("Apilo la estructura pila_t",pila_apilar(pila8,pila8));
	print_test("Apilo la  estructura tipo_t",pila_apilar(pila8,temp));
	print_test("La pila no esta vacia",!pila_esta_vacia(pila8));
	printf("Desapilo  el struct tipo_t \n");
	pila_desapilar(pila8);
	printf("Desapilo el struct pila_t \n");
	pila_desapilar(pila8);
	print_test("La pila esta vacia",pila_esta_vacia(pila8));	
	pila_destruir(pila8);
	free(temp);
	
}

void pruebas_pila_alumno() {
	pruebas_pila_vacia();
	pruebas_apilar_desapilar_elementos();
	prueba_destruir_elementos();
	pruebas_volumen();
	prueba_estructuras();
} 

