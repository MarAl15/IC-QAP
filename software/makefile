all:  practica2

practica2:	main.o datos.o funciones.o AGmej.o busquedaLocal.o
	g++ -g -o BIN/practica2 obj/main.o obj/datos.o obj/funciones.o obj/AGmej.o obj/busquedaLocal.o -O2

main.o:	src/main.cpp include/datos.h
	g++ -g -c -o obj/main.o src/main.cpp -I./include -O2

datos.o: src/datos.cpp include/datos.h 
	g++ -g -c -o obj/datos.o -I./include src/datos.cpp -O2

funciones.o: src/funciones.cpp include/funciones.h 
	g++ -g -c -o obj/funciones.o -I./include src/funciones.cpp -O2
		
AGmej.o: src/AGmej.cpp include/AGmej.h 
	g++ -g -c -o obj/AGmej.o -I./include src/AGmej.cpp -O2
	
busquedaLocal.o: src/busquedaLocal.cpp include/busquedaLocal.h 
	g++ -g -c -o obj/busquedaLocal.o -I./include src/busquedaLocal.cpp -O2


clean:
	rm obj/*.o
