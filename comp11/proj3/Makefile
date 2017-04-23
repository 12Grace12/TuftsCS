## Makefile for Project 3, wordfreq
## To build phase 1, type 
##    make wordfreq1
## To build phase 2, type
##    make wordfreq2
##
## CAUTION:  Do NOT name a .h file FrequencyTable.h!  
##           It will be deleted.  
##           You write Make FrequencyTable1.h and Frequency2.h.
##

CXX      = g++
CPPFLAGS = -g -Wall -Wextra
LFLAGS   = -g

wordfreq1: wordfreq1.o FrequencyTable1.o WordFreqList.o
	$(CXX) $(LFLAGS) -o $@ $^ 

wordfreq2: wordfreq2.o FrequencyTable2.o WordFreqList.o
	$(CXX) $(LFLAGS) -o $@ $^ 

wordfreq1.o: wordfreq.cpp header1
	$(CXX) $(CPPFLAGS) -o $@ wordfreq.cpp -c

wordfreq2.o: wordfreq.cpp header2
	$(CXX) $(CPPFLAGS) -o $@ wordfreq.cpp -c

header1:
	rm -f FrequencyTable.h
	ln -s FrequencyTable1.h FrequencyTable.h

header2:
	rm -f FrequencyTable.h
	ln -s FrequencyTable2.h FrequencyTable.h

wfltest.o: wfltest.cpp

wfltest:  wfltest.o WordFreqList.o
	$(CXX) $(LFLAGS) -o $@ $^ 

WordFreqList.o:  WordFreqList.cpp WordFreqList.h
FrequencyTable1.o: FrequencyTable1.cpp FrequencyTable1.h
FrequencyTable2.o: FrequencyTable2.cpp FrequencyTable2.h


# .o.cpp:
# 	$(CXX) $(CPPFLAGS) -c $<

clean:
	rm -rf *~ *.o wordfreq1 wordfreq2 wfltest FrequencyTable.h
