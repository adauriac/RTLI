CPPFLAGS =  -Wall -O3

callAndAnalyze:callAndAnalyze.cpp libRFIM1d.o Makefile
	g++ callAndAnalyze.cpp libRFIM1d.o -o  callAndAnalyze $(CPPFLAGS)

call5 : call5.cpp libRFIM1d.o Makefile
	g++ call5.cpp libRFIM1d.o -o call5  $(CPPFLAGS)

call4 : call4.cpp libRFIM1d.o Makefile
	g++ call4.cpp libRFIM1d.o -o call4  $(CPPFLAGS)

call3 : call3.cpp libRFIM1d.o Makefile
	g++ call3.cpp libRFIM1d.o -o call3  $(CPPFLAGS)

call2 : call2.cpp libRFIM1d.o Makefile
	g++ call2.cpp libRFIM1d.o -o call2  $(CPPFLAGS)

call1 : call1.cpp libRFIM1d.o Makefile
	g++ call1.cpp libRFIM1d.o -o call1 - $(CPPFLAGS)

libRFIM1d.o : libRFIM1d.cpp RFIM1d.h Makefile
	g++ libRFIM1d.cpp -c $(CPPFLAGS)
