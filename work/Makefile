
call4 : call4.cpp libRFIM1d.o Makefile
	g++ call4.cpp libRFIM1d.o -o call4 -Wall -O3

call3 : call3.cpp libRFIM1d.o Makefile
	g++ call3.cpp libRFIM1d.o -o call3 -Wall -O3

call2 : call2.cpp libRFIM1d.o Makefile
	g++ call2.cpp libRFIM1d.o -o call2 -Wall -O3 

call1 : call1.cpp libRFIM1d.o Makefile
	g++ call1.cpp libRFIM1d.o -o call1 -Wall -O3

libRFIM1d.o : libRFIM1d.cpp RFIM1d.h Makefile
	g++ libRFIM1d.cpp -Wall -O3 -c
