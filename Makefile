out: obj/city.o obj/weatherview.o obj/tile.o \
		obj/dashboard.o obj/database.o obj/dbtest.o
	g++ obj/city.o obj/weatherview.o obj/tile.o \
		obj/dashboard.o obj/database.o obj/dbtest.o \
		-Iinclude -I/usr/include -L/usr/lib -lPocoFoundation \
		-lPocoData -lPocoDataSQLite -g

obj/city.o: include/city.h src/city.cpp
	g++ src/city.cpp -Iinclude -g -c -o obj/city.o

obj/weatherview.o: include/weatherview.h src/weatherview.cpp
	g++ src/weatherview.cpp -Iinclude -g -c -o obj/weatherview.o

obj/tile.o: include/tile.h src/tile.cpp
	g++ src/tile.cpp -Iinclude -g -c -o obj/tile.o

obj/dashboard.o: include/dashboard.h src/database.cpp
	g++ src/dashboard.cpp -Iinclude -g -c -o obj/dashboard.o

obj/database.o: include/database.h src/database.cpp
	g++ src/database.cpp -Iinclude -g -c -o obj/database.o

obj/dbtest.o: src/dbtest.cpp
	g++ src/dbtest.cpp -Iinclude -g -c -o obj/dbtest.o

