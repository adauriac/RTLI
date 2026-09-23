libRFIM1d.o : libRFIM1d.cpp RFIM1d.h Makefile
	g++ libRFIM1d.cpp -Wall -O3 -c

call1 : call1.cpp libRFIM1d.o Makefile
	g++ call1.cpp libRFIM1d.o -o call1 -Wall -O3 -o call1
