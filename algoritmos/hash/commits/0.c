#include "hash.h"
#include "lista.h"
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#define TAM_INI 191

struct hash{
  lista_t** tabla;
  unsigned long largo;
  unsigned long tam;
  hash_destruir_dato_t destruir_dato; 
};

struct hash_iter{
  const hash_t* hash;
  size_t indice_actual;
  lista_iter_t* iter_lista;
};

typedef struct daton{
  char* clave;
  void* dato;
}daton_t;



unsigned long fh(const  char *str, unsigned long  tam)  {
        unsigned long hash = 0;
        int c;

        while ((c = *str++))
            hash = c + (hash << 6) + (hash << 16) - hash;
        return hash % tam;
}
/* Crea el hash
 */

char *strdup (const char *s) {
    char *d = malloc (strlen (s) + 1);   // Space for length plus nul
    if (d == NULL) return NULL;          // No memory
    strcpy (d,s);                        // Copy the characters
    return d;                            // Return the new string
}

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
  hash_t* hash = malloc(sizeof(hash_t));
  if (!hash) return NULL;
  hash->tabla = malloc(TAM_INI * sizeof(lista_t*));
  if (!hash->tabla) {
    free(hash);
    return NULL;
  }
  hash->largo = TAM_INI;
  hash->tam = 0;
  hash->destruir_dato = destruir_dato;
  for (int i = 0; i < hash->largo; i++){
    hash->tabla[i] = NULL;
  }
  return hash;
}

daton_t* paquete_crear(const char* clave, void*  dato){
  daton_t* paquete = malloc(sizeof(daton_t));
  if (!paquete) return NULL;
  paquete->clave = strdup(clave);
  if (!paquete->clave) {
    free(paquete);
    return NULL;
  }
  paquete->dato = dato;
  return paquete;
}

lista_iter_t* busqueda(lista_t* lista, const char* clave){
  lista_iter_t* iter = lista_iter_crear(lista);
  daton_t* aux= lista_iter_ver_actual(iter);
  while (!lista_iter_al_final(iter)  && strcmp(aux->clave, clave) != 0) {
    lista_iter_avanzar(iter);
    aux= lista_iter_ver_actual(iter);
  }
  return iter;
}

bool almacenar(hash_t* hash, lista_t** tabla, daton_t* paquete, unsigned long largo){
  bool resu;
  unsigned long indice = fh(paquete->clave, largo );
  if (!tabla[indice]){
    tabla[indice] = lista_crear();
  }
  lista_iter_t* iter_l = busqueda(tabla[indice], paquete->clave);
  if (lista_iter_al_final(iter_l)) {  //no lo encontro
    resu = lista_insertar_primero(tabla[indice], paquete);
    hash->tam++;
    lista_iter_destruir(iter_l);
    return resu;
  }
  daton_t* aux = lista_iter_borrar(iter_l);
  free(aux->clave);
  if (hash->destruir_dato) hash->destruir_dato(aux->dato); 
  free(aux);
  resu = lista_insertar_ultimo(tabla[indice], paquete);
  lista_iter_destruir(iter_l);
  return resu;
}

bool redimensionar(hash_t* hash, unsigned long nuevo_largo){
  lista_t** nueva_tabla = malloc(sizeof(lista_t*) * nuevo_largo);
  for (int i = 0; i < nuevo_largo; i++){
    nueva_tabla[i] = NULL;
  }
  lista_iter_t* iter_lista = NULL;
  daton_t* paquete;
  hash->tam = 0;
  for (int a = 0; a < hash->largo ; a++){
    if (hash->tabla[a]){
      iter_lista = lista_iter_crear(hash->tabla[a]);
      while (!lista_iter_al_final(iter_lista)){
	paquete = lista_iter_ver_actual(iter_lista);
	almacenar(hash, nueva_tabla, paquete, nuevo_largo);
	lista_iter_avanzar(iter_lista);
      }
      lista_iter_destruir(iter_lista);    
      lista_destruir(hash->tabla[a], NULL);
    }
  }
  hash->largo = nuevo_largo;
  free(hash->tabla) ;
  hash->tabla = nueva_tabla;
  return true;
}


bool hash_guardar(hash_t *hash, const char *clave, void *dato){
  bool res;
  daton_t* paquete = paquete_crear(clave, dato);
  if (hash->tam > 3 * hash->largo) {
    unsigned long  nuevo_largo = ( hash->largo * 3);
    redimensionar(hash, nuevo_largo);
  }
  res = almacenar(hash, hash->tabla, paquete, hash->largo); 
  return res;
}


void *hash_borrar(hash_t *hash, const char *clave){
  unsigned long indice = fh(clave,hash->largo);
  if (!hash->tabla[indice]) return NULL;
  lista_iter_t* iter_l = busqueda(hash->tabla[indice], clave);
  if (lista_iter_al_final(iter_l)) {
    lista_iter_destruir(iter_l);
    return NULL;
  }
  daton_t* aux = lista_iter_borrar(iter_l);
  void* dato_salida = aux->dato; 
  free(aux->clave);
  free(aux);
  hash->tam--;
  lista_iter_destruir(iter_l);
  if (lista_esta_vacia(hash->tabla[indice])){
    lista_destruir(hash->tabla[indice], NULL);
    hash->tabla[indice] = NULL;
  }
  if (hash->tam < 3 * hash->largo && hash->largo > TAM_INI) {
    unsigned long  nuevo_largo = hash->largo /  2;
    redimensionar(hash, nuevo_largo);
  }
  return dato_salida;
}

/* Obtiene el valor de un elemento del hash, si la clave no se encuentra
 * devuelve NULL.
 * Pre: La estructura hash fue inicializada
 */
void *hash_obtener(const hash_t *hash, const char *clave){
  unsigned long indice = fh(clave, hash->largo);
  if (!hash->tabla[indice]) return NULL;
  lista_iter_t* iter_l = busqueda(hash->tabla[indice], clave);
  if (lista_iter_al_final(iter_l)) {
    lista_iter_destruir(iter_l);
    return NULL;
  }
  daton_t* aux = lista_iter_ver_actual(iter_l);
  void* dato_salida = aux->dato;
  lista_iter_destruir(iter_l);
  return dato_salida;
}


bool hash_pertenece(const hash_t *hash, const char *clave){
  unsigned long indice = fh(clave, hash->largo);
  if (!hash->tabla[indice]) return false;
  lista_iter_t* iter_l = busqueda(hash->tabla[indice], clave);
  if (lista_iter_al_final(iter_l)) {
    lista_iter_destruir(iter_l);
    return false;
  }
  lista_iter_destruir(iter_l);
  return true;
}

size_t hash_cantidad(const hash_t *hash){
  return hash->tam;
}

void lista_destruir2(lista_t* lista, hash_destruir_dato_t destruir_dato){ // Funcion que cree parecida a la de la lista, ya que la otra no me servia
  if (lista_esta_vacia(lista)){
    free(lista);
    return;
  }
  if (destruir_dato){
    daton_t* aux = lista_borrar_primero(lista);
    free(aux->clave);
    destruir_dato(aux->dato);
    free(aux);
    lista_destruir2(lista, destruir_dato);
    return;
  }
  daton_t* aux2 = lista_borrar_primero(lista);
  free(aux2->clave);
  free(aux2);
  lista_destruir2(lista, destruir_dato);
}


void hash_destruir(hash_t *hash){
  for (int i = 0; i < hash->largo; i++){
    if (hash->tabla[i]) {
      lista_destruir2(hash->tabla[i], hash->destruir_dato);
    }
  } 
  free(hash->tabla);
  free(hash);
}

/* Iterador del hash */


hash_iter_t *hash_iter_crear(const hash_t *hash){
  hash_iter_t* iter = malloc(sizeof(hash_iter_t));
  if (!hash) return NULL;
  iter->hash = hash;
  iter->iter_lista = NULL;
  iter->indice_actual = 0;
  for(int i= 0; i < hash->largo; i++){
    if (hash->tabla[i]){
      iter->iter_lista = lista_iter_crear(hash->tabla[i]);  
      iter->indice_actual = i ;
      return iter;
    }
    iter->indice_actual = i ;
  }
  return iter;
}

bool hash_iter_avanzar(hash_iter_t *iter){
  if(hash_iter_al_final(iter)) return false;
  lista_iter_avanzar(iter->iter_lista);
  if (lista_iter_al_final(iter->iter_lista)) {
    iter->indice_actual++;
    while (iter->indice_actual < iter->hash->largo){
      if (iter->hash->tabla[iter->indice_actual]){
	lista_iter_destruir(iter->iter_lista);
	iter->iter_lista = lista_iter_crear(iter->hash->tabla[iter->indice_actual]);
	return true;
      }
      iter->indice_actual++;
    }
  }
  return true;
}


const char *hash_iter_ver_actual(const hash_iter_t *iter){
  if (hash_iter_al_final(iter)) return NULL;
  daton_t* aux = lista_iter_ver_actual(iter->iter_lista);
  if (!aux) return NULL;
  return aux->clave;
}


bool hash_iter_al_final(const hash_iter_t *iter){
  if (iter->hash->tam == 0 || iter->indice_actual > iter->hash->largo-1) return true;
  if (iter->indice_actual == iter->hash->largo-1 && lista_iter_al_final(iter->iter_lista)) return true;
  return false;
}

void hash_iter_destruir(hash_iter_t* iter){
  lista_iter_destruir(iter->iter_lista);
  free(iter);
}
