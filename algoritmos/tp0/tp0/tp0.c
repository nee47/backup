#include "tp0.h"

/* ******************************************************************
 *                     FUNCIONES A COMPLETAR
 * *****************************************************************/

/* swap() intercambia dos valores enteros.
 */
void swap (int* x, int* y) {
  int temp;
  temp=*x;
  *x=*y;
  *y=temp;
}

/* maximo() busca el mayor elemento del arreglo y devuelve su posicion.
 * Si el vector es de largo 0, devuelve -1.
 */
int maximo(int vector[], int n) {
  int i;
  int pos;	
  if (n==0) return -1;  
  pos=0;
  for(i=0;i<n;i++){
    if (vector[pos]<vector[i]){ 
      pos=i;
    }
  }
	
  return pos;
}

/* La función comparar recibe dos vectores y sus respectivas longitudes
 * y devuelve -1 si el primer vector es menor que el segundo; 0 si son
 * iguales; y 1 si el segundo es menor.
 *
 * Un vector es menor a otro cuando al compararlos elemento a elemento,
 * el primer elemento en el que difieren no existe o es menor.
 */
int comparar(int vector1[], int n1, int vector2[], int n2) {
  int i,naux;
  if (n1>n2) naux=n2;
  if (n1<n2) naux=n1;
  if (n1==n2) naux=n1;
  for (i=0;i<naux;i++){
    if (vector1[i]>vector2[i]) return 1;	
    if (vector1[i]<vector2[i]) return -1;		
  }
  if (n1>n2) return 1;
  if (n1<n2) return -1;
  return 0;
}

/* selection_sort() ordena el arreglo recibido mediante el algoritmo de
 * selección.
 */
void seleccion(int vector[], int n) {
  int posmax,i;     
  for(i=0;i<n;i++){ 		
    posmax=maximo(vector,n-i);
    swap(&vector[n-i-1],&vector[posmax]);	
  }
}
