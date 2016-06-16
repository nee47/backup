#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define TAM_PRUEBAS 50000
typedef struct tipo{
	void* dato;
} tipo_t;
typedef struct tipu{
	void* simo;
}tipu_t;


 typedef struct vector{
	void** dato;
	size_t largo;
 } vector_t; 
 
vector_t* crear_cargar_vector(){
	vector_t* vec=malloc(sizeof(vector_t));
	if (vec==NULL) return NULL;
	vec->dato=malloc(2*sizeof(vec->dato));
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
void pruebas_cola_vacia(){
  printf("***** Inicio de pruebas cola vacia *****\n");
  cola_t* cola = cola_crear();
  print_test("cola creada con exito  ",cola!=NULL);
  print_test("cola esta vacia ",cola_esta_vacia(cola));
  print_test("cola ver primero devuelve NULL", !cola_ver_primero(cola));
  print_test("cola desencolar devuelve NULL", !cola_desencolar(cola));	
  cola_destruir(cola,NULL);
}


void pruebas_encolar_desencolar(){ 
  printf("\n ***Inicio de pruebas cola_encolar cola_desencolar *** \n");
  int a=3;
  int b=1;
  cola_t* cola = cola_crear();
	
  print_test("Encolo el elemento 3 cola2",cola_encolar(cola,&a));
  print_test("La cola no esta vacia",!cola_esta_vacia(cola));
  print_test("Encolo el elemento 1 cola2",cola_encolar(cola,&b));
  print_test("Encolo el numero 3 cola2",cola_encolar(cola,&a));
  print_test("Ver primero me devuelve 3 ",*(int*)cola_ver_primero(cola)==3);
  print_test("Desencolo el primer elemento y devuelve valor ",*(int*)cola_desencolar(cola)==3);
  print_test("Ver primero me devuelve 1 ",*(int*)cola_ver_primero(cola)==1);
  print_test("Desencolo el primer elemento y devuelve valor ",*(int*)cola_desencolar(cola)==1);
  print_test("Ver primero me devuelve 3 ",*(int*)cola_ver_primero(cola)==3);
  print_test("Desencolo el primer elemento y devuelve valor ",*(int*)cola_desencolar(cola)==3);
  print_test("Devuelve NUll Cuando ya no hay elementos para desencolar",cola_desencolar(cola)==NULL);
  print_test("la cola esta vacia", cola_esta_vacia(cola));
  print_test("Vuelvo a encolar el elemento 3 ",cola_encolar(cola,&a));
  print_test("Vuelvo a encolar el elemento 1 ",cola_encolar(cola,&b));
  print_test("**Cola destrida con elementos **",true);
  cola_destruir(cola,NULL);
  

}


void pruebas_structs(){
  /*   PRUEBA CON FUNCION FREE */
  printf("\n ***Inicio de pruebas con structs *** \n");
  printf("PRUEBAS CON FUNCION FREE \n");
  cola_t* cola3=cola_crear();
  cola_t* cola4=cola_crear();
  tipo_t* temp1=malloc(sizeof(tipo_t));
  tipo_t* temp2=malloc(sizeof(tipo_t));
  print_test("Encolo un  cola_t ",cola_encolar(cola3,cola4));
  print_test("Encolo un  tipo_t",cola_encolar(cola3,temp1));
  print_test("Encolo un  tipo_t",cola_encolar(cola3,temp2));
  print_test("cola no esta vacia",!cola_esta_vacia(cola3));
  cola_destruir(cola3, free); 
  
  cola_t* cola5 = cola_crear();
  cola_destruir(cola5, NULL);
  
  /*  PRUEBA CON FUNCION DISTINTO DE FREE*/
  printf("\n PRUEBAS CON FUNCION DISTINTO DE FREE \n");
  vector_t* vec1 = crear_cargar_vector();
  vector_t* vec2 = crear_cargar_vector();
  vector_t* vec3 = crear_cargar_vector();
  
  cola_t* cola = cola_crear();
  print_test("la cola esta vacia",cola_esta_vacia(cola));
  print_test("cola encolar vec1 ", cola_encolar(cola, vec1));
  print_test("cola no esta vacia", !cola_esta_vacia(cola));
  print_test("cola ver primero es vec1", cola_ver_primero(cola) == vec1);
  print_test("cola encolar vec2 ", cola_encolar(cola, vec2));
  print_test("cola ver primero sigue siendo vec1", cola_ver_primero(cola) == vec1);
  print_test("cola encolar ve3", cola_encolar(cola, vec3));
  
  cola_destruir(cola, destruir_vector);
  print_test("cola destruid",true);

}

void pruebas_volumen(){
  printf("***** Inicio de pruebas de volumen *****\n");
  
  bool ok = true;

  cola_t* cola = cola_crear();
  print_test("cola esta vacia", cola_esta_vacia(cola));
  int vec[TAM_PRUEBAS];
  for(int a =0; a < TAM_PRUEBAS; a++){
    vec[a] = a;
    ok = cola_encolar(cola, &vec[a]);
    if (!ok) break;    
  }
  
  print_test("Todos los elementos fueron encolados con exito", ok);

  for(int b = 0; b < TAM_PRUEBAS ; b++){
    ok = *(int*)cola_desencolar(cola) == vec[b] ? true : false ;
    if (!ok) break;
  }
  
  print_test("Todos los elementos fueron desencolados en orden", ok);
  
  cola_destruir(cola, NULL);
}


void pruebas_cola_alumno(){
	pruebas_cola_vacia();
	pruebas_encolar_desencolar();
	pruebas_structs();
	pruebas_volumen();

}

