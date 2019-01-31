all:  practica2

practica2:	main.o datos.o funciones.o AG.o AGE.o busquedaLocal.o AGE-BL.o
	g++ -g -o BIN/practica2 obj/main.o obj/datos.o obj/funciones.o obj/AG.o obj/AGE.o obj/busquedaLocal.o obj/AGE-BL.o -O2

main.o:	src/main.cpp include/datos.h
	g++ -g -c -o obj/main.o src/main.cpp -I./include -O2

datos.o: src/datos.cpp include/datos.h 
	g++ -g -c -o obj/datos.o -I./include src/datos.cpp -O2

funciones.o: src/funciones.cpp include/funciones.h 
	g++ -g -c -o obj/funciones.o -I./include src/funciones.cpp -O2
	
AG.o: src/AG.cpp include/AG.h 
	g++ -g -c -o obj/AG.o -I./include src/AG.cpp -O2
		
AGE.o: src/AGE.cpp include/AGE.h 
	g++ -g -c -o obj/AGE.o -I./include src/AGE.cpp -O2

AGE-BL.o: src/AGE-BL.cpp include/AGE-BL.h 
	g++ -g -c -o obj/AGE-BL.o -I./include src/AGE-BL.cpp -O2
	
busquedaLocal.o: src/busquedaLocal.cpp include/busquedaLocal.h 
	g++ -g -c -o obj/busquedaLocal.o -I./include src/busquedaLocal.cpp -O2


clean:
	rm obj/*.o
