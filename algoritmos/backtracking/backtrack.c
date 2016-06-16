TAblero = (fila[0...n-1]) of boolean;
  diagonal mas{-n+1 ...n-1};
  diagonal menos {0 .. 2n-2};
  solucion= lista de enteros;
  cuantos_puse int

  )

  Reinas(N) = ExtenderBackREinas(N, tablero vacio)
     extemder back reinas(N, tablero)   
     si tablero.cuantospuse == N : return [tablero solucion] 
     sino 
         sol = [] 
         para todo i = 0 hasta n-1
             si esfactible(tablero, cuantospuse+1, i))
	        sol += ebr(n, EXTENDER(tablero, cuantospuse+1, i))
