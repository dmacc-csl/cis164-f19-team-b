
# core object list
OBJECTS=obj/city.o obj/weatherview.o obj/tile.o \
		obj/dashboard.o obj/database.o

# use -g for debug flags
G=-g

# use to generate profiler file
PG=-pg

# database tester
testdb: ${OBJECTS} obj/dbtest.o
	g++ ${OBJECTS} obj/dbtest.o -Iinclude -I/usr/include -L/usr/lib \
		-lPocoFoundation -lPocoData -lPocoDataSQLite ${G} ${PG}

# core objects
obj/city.o: include/city.h src/city.cpp
	g++ src/city.cpp -Iinclude ${G} -c -o obj/city.o

obj/weatherview.o: include/weatherview.h src/weatherview.cpp
	g++ src/weatherview.cpp -Iinclude ${G} -c -o obj/weatherview.o

obj/tile.o: include/tile.h src/tile.cpp
	g++ src/tile.cpp -Iinclude ${G} -c -o obj/tile.o

obj/dashboard.o: include/dashboard.h src/database.cpp
	g++ src/dashboard.cpp -Iinclude ${G} -c -o obj/dashboard.o

obj/database.o: include/database.h src/database.cpp
	g++ src/database.cpp -Iinclude ${G} -c -o obj/database.o

obj/dbtest.o: src/dbtest.cpp
	g++ src/dbtest.cpp -Iinclude ${G} -c -o obj/dbtest.o

# clean binaries and object files
clean:
	rm *.out obj/*

