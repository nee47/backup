
#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define TAM_PRUEBAS 80000
typedef struct vector{
  void** dato;
  size_t largo;
} vector_t; 
 
typedef struct tipu{
	void* simo;
}tipu_t;

vector_t* crear_cargar_vector(){
	vector_t* vec=malloc(sizeof(vector_t));
	if (vec==NULL) return NULL;
	vec->dato=malloc(2*sizeof(void*));
	int* a=malloc(sizeof(int));
	int* b=malloc(sizeof(int));
	
	vec->dato[0]=a;
	vec->dato[1]=b;
	vec->largo=2;
	return vec;
} 

void destruir_vector(void* vec){
	vector_t* vector=vec;
	size_t a;
	for(a=0;a<vector->largo;a++){
		free(vector->dato[a]);
	}
	free(vector->dato);
	free(vector);
}

void pruebas_lista_vacia(){
  printf(" - PRUEBAS LISTA VACIA -  \n");
  lista_t* lista = lista_crear();
  print_test("Lista esta vacia", lista_esta_vacia(lista));
  print_test("Lista largo es 0", lista_largo(lista) == 0);
  print_test("Lista ver primero devuelve NULL ", !lista_ver_primero(lista));
  print_test("Lista borrar primero devuelve NULL", !lista_borrar_primero(lista));
  lista_destruir(lista, NULL);
  print_test("lista destruida", true);
  
  /*   PRUEBAS LISTA VACIA CON ITERADORES  */
  printf(" \n PRUEBAS LISTA VACIA CON ITERADOR \n");
  lista_t* lista2 = lista_crear();
  lista_iter_t* iter = lista_iter_crear(lista2);

  print_test("Lista2 esta vacia", lista_esta_vacia(lista2));
  print_test("Lista2 largo es 0", lista_largo(lista2) == 0);
  print_test("Lista2 ver primero devuelve NULL ", !lista_ver_primero(lista2));
  print_test("Lista2 borrar primero devuelve NULL", !lista_borrar_primero(lista2));
  
  print_test("iter esta al final", lista_iter_al_final(iter));
  print_test("iter avanzar devuelve NULL", !lista_iter_avanzar(iter));
  print_test("iter ver actual devuelve NULL", !lista_iter_ver_actual(iter));
  print_test("iter borrar devuelve NULL", !lista_iter_borrar(iter));
  lista_iter_destruir(iter);
  print_test("iter destruido ", true);
  lista_destruir(lista2, NULL);
  print_test("lista destruida ", true );
  
}


void pruebas_lista_insertar_borrar(){
  printf("\n  PRUEBAS INSERTAR BORRAR \n");
  lista_t* lista = lista_crear();
  int a = 5 , b = 10, c = 15 , d = 20 ;
  
  print_test("lista esta vacia", lista_esta_vacia(lista));
  print_test("lista insertar primero 5  ", lista_insertar_primero(lista, &a));
  print_test("lista no esta vacia ", !lista_esta_vacia(lista));
  print_test("lista ver primero  es 5", *(int*)lista_ver_primero(lista) == a);
  print_test("lista inserar primero 10 ", lista_insertar_primero(lista, &b));
  print_test("list ver primero es 10", *(int*)lista_ver_primero(lista) == b);
  print_test("lista insertar ultimo 15 ", lista_insertar_ultimo(lista, &c));
  print_test("lista  largo es 3 ", lista_largo(lista) == 3);
  print_test("lista ver primero sigue siendo 10", lista_ver_primero(lista));
  print_test("lista insetar ultimo  20", lista_insertar_ultimo(lista, &d));
  print_test("lista largo ahora es 4 ", lista_largo(lista) == 4);
  print_test("lista borrar primero deuelve 10", *(int*)lista_borrar_primero(lista) == b);
  print_test("lista largo ahora es 3 ", lista_largo(lista) == 3 );
  print_test("lista borrar primero devuelve 5", *(int*)lista_borrar_primero(lista) == a);
  print_test("lista largo ahora es 2", lista_largo(lista) == 2);
  print_test("lista borrar primero devuelve 15", *(int*)lista_borrar_primero(lista) == c);
  print_test("lista largo ahora es 1", lista_largo(lista) == 1);
  print_test("lista borrar primero devuelve 20", *(int*)lista_borrar_primero(lista) == d );
  print_test("lista largo ahora es 0 ", lista_largo(lista) == 0);
  print_test("lista esta vacia", lista_esta_vacia(lista));
  print_test("vuelvo a insertar primero el 5", lista_insertar_primero(lista, &a));
  print_test("lista no esta vacia", !lista_esta_vacia(lista));
  print_test("lista largo es 1", lista_largo(lista) == 1);
  print_test("vuelvo a insertar ultimo el 10", lista_insertar_ultimo(lista, &b));
  print_test("lista largo es 2", lista_largo(lista) == 2);
  print_test("vuevo a borrar primero y devuelve 5", *(int*)lista_borrar_primero(lista) == a);
  print_test("lista largo ahora es 1 ", lista_largo(lista) == 1);
  print_test("vuelvo a borrar primero y devuelve 10", *(int*)lista_borrar_primero(lista) == b);
  print_test("lista largo ahora es 0", lista_largo(lista) == 0);
  print_test("lista esta vacia", lista_esta_vacia(lista));
  
  lista_destruir(lista, NULL);
  print_test("la lista ha sido destruida", true);


}

void pruebas_destruccion(){ // con memoria dinamica
  printf(" \n INICIO DE PRUEBAS DE DESTRUCCION Y MEMORIA DINAMICA \n");
  /* PRUEBA CON NULL */
  int a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5 ;
  
  lista_t* list = lista_crear();
  
  print_test("list esta vacia", lista_esta_vacia(list));
  print_test("list insertar ultimo a1", lista_insertar_ultimo(list, &a1));
  print_test("list insertar ultimo a2", lista_insertar_ultimo(list, &a2));
  print_test("list insertar ultimo a3", lista_insertar_ultimo(list, &a3));
  print_test("list insertar ultimo a4", lista_insertar_ultimo(list, &a4));
  print_test("list insertar ultimo a5", lista_insertar_ultimo(list, &a5));

  lista_destruir(list, NULL);
  /*  PRUEBA CON FUNCION FREE */
  
  lista_t* lista = lista_crear();
  
  int* a = malloc(sizeof(int));
  int* b = malloc(sizeof(int));
  int* c = malloc(sizeof(int));
  
  print_test("lista esta vacia", lista_esta_vacia(lista));
  print_test("lista insertar primero a ", lista_insertar_primero(lista, a));
  print_test("lista insertar ultimo b", lista_insertar_ultimo(lista, b));
  print_test("lista insertar ultimo c", lista_insertar_ultimo(lista, c));
  print_test("lista no esta vacia", !lista_esta_vacia(lista));
  lista_destruir(lista, free);
  print_test("Lista destruida", true);
  
  printf("\n  PRUEBAS CON FUNCION DISTINTA A FRE \n");

  /* PRUEBA CON FUNCION DISTINTA A FREE */ 
  
  lista_t* lista2 = lista_crear();
  
  vector_t* vec1 = crear_cargar_vector();
  vector_t* vec2 = crear_cargar_vector();
  vector_t* vec3 = crear_cargar_vector();
  
  print_test("lista2 esta vacia", lista_esta_vacia(lista2));
  print_test("lista2 insertar primero vec1 ", lista_insertar_primero(lista2, vec1));
  print_test("lista2 insertar ultimo vec2 ", lista_insertar_ultimo(lista2, vec2));
  print_test("lista2 insertar ultimo vec3", lista_insertar_ultimo(lista2, vec3));
  print_test("lista2 no esta vacia ", !lista_esta_vacia(lista2));
  print_test("lista2 ver primero es vec 1", lista_ver_primero(lista2) == vec1);
  lista_destruir(lista2, destruir_vector);
  print_test("lista destruida ", true);
}


void pruebas_iterador_externo(){
  lista_t* lista = lista_crear();
  int a = 1,b = 2,c = 1,d = 1,e = 1,f = 2,g = 1;
  int c0 =5, c1 = 10, cm = 15, c2 = 20, c3 = 30, c4 = 40;

  print_test("lista esta vacia ", lista_esta_vacia(lista));
  print_test("lista insertar ultimo 10", lista_insertar_ultimo(lista, &c1));
  print_test("lista insertar ultimo 20", lista_insertar_ultimo(lista, &c2));
  print_test("lista insertar ultimo 30", lista_insertar_ultimo(lista, &c3));
  print_test("lista insertar ultimo 40", lista_insertar_ultimo(lista, &c4));
  print_test("lista largo", lista_largo(lista) == 4);
  
  lista_iter_t* iter = lista_iter_crear(lista);

  print_test("iter no esta al final", !lista_iter_al_final(iter));
  print_test("iter ver actual devuelve 10", *(int*)lista_iter_ver_actual(iter) == c1);
  print_test("iter avanzar devuelve true", lista_iter_avanzar(iter));
  print_test("iter no esta al final", !lista_iter_al_final(iter));
  print_test("iter ver actual devuelve 20", *(int*)lista_iter_ver_actual(iter) == c2);
  print_test("iter avanzar devuelve true", lista_iter_avanzar(iter));
  print_test("iter no esta al final", !lista_iter_al_final(iter));
  print_test("iter ver actual devuelve 30", *(int*)lista_iter_ver_actual(iter) == c3);
  print_test("iter avanzar devuelve true", lista_iter_avanzar(iter));
  print_test("iter no esta al final", !lista_iter_al_final(iter));
  print_test("iter ver actual  devuelve 40 ", *(int*)lista_iter_ver_actual(iter) == c4);
  lista_iter_destruir(iter);
  /*  pruebo borrar con iter1 */
  lista_iter_t* iter1 = lista_iter_crear(lista);
  print_test("iter1 ver actual es 10", *(int*)lista_iter_ver_actual(iter1) == 10);
  print_test("iter1 avanzar", lista_iter_avanzar(iter1));
  print_test("iter1 ver actual ahora es 20", *(int*)lista_iter_ver_actual(iter1));
  print_test("iter1 avanzar", lista_iter_avanzar(iter1));
  print_test("iter1 ver actual ahora es 30", *(int*)lista_iter_ver_actual(iter1) == c3);
  print_test("iter1 borrar devuelve 30", *(int*)lista_iter_borrar(iter1) == c3);
  print_test("iter1 ver actual es 40", *(int*)lista_iter_ver_actual(iter1) == c4);
  print_test("lista largo ahora es 3", lista_largo(lista) == 3);
  print_test("iter1 borrar devuelve 40 ", *(int*)lista_iter_borrar(iter1) == c4);
  print_test("lista largo ahora es 2 ", lista_largo(lista) == 2 );
  print_test("iter1 avanzar es false", !lista_iter_avanzar(iter1));
  print_test("iter1 ahora esta al final", lista_iter_al_final(iter1));
  lista_iter_destruir(iter1);
  /* pruebo insertar con iter2 */
  lista_iter_t* iter2 = lista_iter_crear(lista);
  print_test("iter2 no esta al final", !lista_iter_al_final(iter2));
  print_test("iter2 ver actual es 10", *(int*)lista_iter_ver_actual(iter2) == c1);
  /* inserto al principio*/
  print_test("iter2 insertar 5", lista_iter_insertar(iter2, &c0));
  print_test("lista ver actual ahora es 5 ", *(int*)lista_iter_ver_actual(iter2) == c0);
  print_test("lista largo ahora es 3", lista_largo(lista) == 3 );
  /* inserto por el medio  */
  print_test(" iter2 avanzar devuelve true  ", lista_iter_avanzar(iter2));
  print_test("iter2 ver actual es 10", *(int*)lista_iter_ver_actual(iter2) == c1);
  print_test(" iter2 avanzar devuelve true ", lista_iter_avanzar(iter2));
  print_test("iter2 ver actual es 20", *(int*)lista_iter_ver_actual(iter2) == c2);
  print_test("iter2 insertar 15 ", lista_iter_insertar(iter2, &cm));
  print_test("iter2 ver actual es 15", *(int*)lista_iter_ver_actual(iter2) == cm);
  print_test("lista largo ahora es 4", lista_largo(lista) == 4); 
  print_test("iter2 avanzar devuelve true ", lista_iter_avanzar(iter2));
  print_test("iter2 ver actual devuelve 20", *(int*)lista_iter_ver_actual(iter2) == c2);
  print_test("iter2 no esta al final", !lista_iter_al_final(iter2));
  print_test("iter2 avanzar es true", lista_iter_avanzar(iter2));
  print_test("iter2 esta al final", lista_iter_al_final(iter2));
  print_test("iter2  insertar es true ", lista_iter_insertar(iter2, &c0));
  print_test("inserte y ya no esta al final", !lista_iter_al_final(iter2));
  print_test("iter 2 ver actual devuelve 5", *(int*)lista_iter_ver_actual(iter2) == c0);
  lista_iter_destruir(iter2);
  lista_destruir(lista, NULL);
  

  lista_t* listan=lista_crear();
  print_test("se creo lista vacia",lista_esta_vacia(listan));
  print_test("Inserto el elemento 1",lista_insertar_ultimo(listan,&a));
  print_test("Inserto el elemento 2",lista_insertar_ultimo(listan,&b));
  print_test("Inserto el elemento 1",lista_insertar_ultimo(listan,&c));
  print_test("Inserto el elemento 1",lista_insertar_ultimo(listan,&d));
  print_test("Inserto el elemento 1",lista_insertar_ultimo(listan,&e));
  print_test("Inserto el elemento 2",lista_insertar_ultimo(listan,&f));
  print_test("Inserto el elemento 1",lista_insertar_ultimo(listan,&g));
  //cuento cuantos "1" hay
  print_test("El  largo de la lista es 7",lista_largo(listan)==7);
  lista_iter_t* itern=lista_iter_crear(listan);
  while(!lista_iter_al_final(itern)){
    if (*(int*)lista_iter_ver_actual(itern)==2){
      lista_iter_borrar(itern);
    }
    lista_iter_avanzar(itern);	
    }
  print_test("Se eliminaron los elementos distintos a 1 y el largo es 5 ",lista_largo(listan)==5);
  
  lista_destruir(listan,NULL);
  lista_iter_destruir(itern);
  
  printf("Prueba  iter insertar con lista vacia \n");
  lista = lista_crear();
  int vaci = 420;
  print_test("lista esta vacia ", lista_esta_vacia(lista));
  iter = lista_iter_crear(lista);
  print_test("lista iter esta al final", lista_iter_al_final(iter));
  print_test("lista iter insertar es true", lista_iter_insertar(iter, &vaci));
  print_test("lista largo es 1", lista_largo(lista) == 1);
  print_test("lista iter no esta al final", !lista_iter_al_final(iter));
  lista_iter_destruir(iter);
  lista_destruir(lista, NULL);
  print_test("lista e iter destruidos", true);
  
}



bool elementos_pares(void* dato, void* extra){
  int* num = extra;
  if (*(int*)dato % 2 ==0 ){
    *num = *num + 1 ;

  }
  return true;
}

bool buscar_cero(void* dato, void* extra){
  int* num = extra;
  *num = *num + 1;
  if(*(int*)dato == 0){
    *num = *num - 1;
    return false;
  }
  return true;
}

bool elemento_en_lista(void* dato,void* elemento){
  int* elem = elemento;
  if (*(int*)dato == *elem){
    *elem = 0 ; // si se encontro el numero elemento se convierte a 0
    return false;	
  }
  return true;
	
}



void pruebas_iterador_interno(){

  printf("\n  Pruebas iterador interno\n");
  lista_t *lista_enteros = lista_crear();
  int a,b,c,d,e;
  a=1;
  b=4;
  c=12;
  d=13;
  e=22;

  print_test("lista esta vacia",lista_esta_vacia(lista_enteros));
  
  print_test("Inserto el elemento 1",lista_insertar_primero(lista_enteros,&a));
  print_test("Inserto el elemento 4",lista_insertar_primero(lista_enteros,&b));
  print_test("Inserto el elemento 12",lista_insertar_primero(lista_enteros,&c));
  print_test("Inserto el elemento 13",lista_insertar_primero(lista_enteros,&d));
  print_test("Inserto el elemento 22",lista_insertar_primero(lista_enteros,&e));
  
  
  int cant_pares = 0;
  int elemento1= 13;
  int elemento2=14;
  int posicion = 0;
  
  lista_iterar(lista_enteros,elementos_pares, &cant_pares);
  print_test("La lista tiene 3 elementos pares",cant_pares == 3);
  
  lista_iterar(lista_enteros,elemento_en_lista,&elemento1);
  print_test("el elemento  13 si se encuentra", elemento1 == 0);
  lista_iterar(lista_enteros, elemento_en_lista,&elemento2);
  print_test("El elemento 14 no se encuentra", elemento2 != 0);
  lista_destruir(lista_enteros,NULL);
  
  lista_t* lista = lista_crear();
  
  int a1 = 1 , a2 = 30, a3 = 23, a4 = 0, a5 = 13, a6= 2, a7=9, a8=0;
  
  lista_iterar(lista, buscar_cero, &posicion);
  print_test("lista iterar lista vacia no modifica posicion", posicion == 0);
  print_test("lista insertar 1", lista_insertar_ultimo(lista, &a1));
  print_test("lista insertar 30",lista_insertar_ultimo(lista, &a2));
  print_test("lista insertar 23",lista_insertar_ultimo(lista, &a3));
  print_test("lista insertar 0",lista_insertar_ultimo(lista, &a4));
  print_test("lista insertar 13",lista_insertar_ultimo(lista, &a5));
  
  print_test("lista insertar 2",lista_insertar_ultimo(lista, &a6));
  
  print_test("lista insertar 9",lista_insertar_ultimo(lista, &a7));
  
  print_test("lista insertar 0",lista_insertar_ultimo(lista, &a8));
  
  lista_iterar(lista, buscar_cero, &posicion);
  print_test("la posicion del 0 es 3 ", posicion == 3);

  lista_destruir(lista, NULL);
}


void pruebas_volumen(){
  printf("PRUEBAS DE VOLUMEN \n");
  bool ok = true ;
  lista_t* lista = lista_crear();
  
  int vec[TAM_PRUEBAS];

  for(int a = 0; a < TAM_PRUEBAS ; a++){
    vec[a] = a;
    ok = lista_insertar_primero(lista, &vec[a]);
    if (!ok ) break;
    ok = *(int*)lista_ver_primero(lista) == vec[a] ? true : false ;
    if (!ok) break;
  }
  
  print_test("Todos los elementos fueron insertados en la lista", ok);
  
  lista_iter_t* iter = lista_iter_crear(lista);
  
  for (int b = 1; !lista_iter_al_final(iter); b++  ){
    ok = *(int*)lista_iter_ver_actual(iter) == vec[TAM_PRUEBAS-b] ? true : false; 
    if (!ok) break;
    ok = lista_iter_avanzar(iter);
    if (!ok) break;
  }
  lista_iter_destruir(iter);
  print_test("los elementos fueron recorridos en orden", ok);

  /* PRUEBA CON ITERADOR IN TERNO */
  // funcion que de vuelve sienpre true
  int cant_pares = 0;
  lista_iterar(lista,elementos_pares, &cant_pares);
  print_test("lista iterar modifica el puntero cantidad de pares a 400000", TAM_PRUEBAS / 2);

  int elemento1 = 35; 
  int elemento2 = 97324;
  int elemento3 = 1560;
  
  lista_iterar(lista,elemento_en_lista,&elemento1);
  print_test("el elemento1 si se encuentra", elemento1 == 0);
  lista_iterar(lista, elemento_en_lista,&elemento3);
  print_test("El elemento3 si se encuentra", elemento3 == 0);
  lista_iterar(lista, elemento_en_lista,&elemento2);
  print_test("El elemento2 no se encuentra", elemento2  != 0);

  lista_destruir(lista, NULL);  
  
}



void pruebas_lista_alumno(){
	pruebas_lista_vacia();
	pruebas_lista_insertar_borrar();
	pruebas_destruccion();
	pruebas_iterador_externo();
	pruebas_iterador_interno();
	pruebas_volumen();
}
