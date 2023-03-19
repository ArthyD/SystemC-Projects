EXEC = fft_test

SRC = $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)
HEA= $(SRC:.cpp=.h) 

CC=g++

#on CentOS
SYSTEMC=/usr/local/bin/Siemens_EDA/Catapult_Synthesis_2022.2_1-1019737/Mgc_home
#on Ubuntu
#SYSTEMC=/usr/home/enstb1/ELEC/SystemC-2.3.3/systemc-2.3.3
#SYSTEMC=/opt/systemc-2.3.3

#on CentOS
LDFLAGS= -L$(SYSTEMC)/lib -L$(SYSTEMC)/shared/lib -Wl,-rpath=$(SYSTEMC)/lib:$(SYSTEMC)/shared/lib -lsystemc -lm
CXXFLAGS= -g -I$(SYSTEMC)/shared/include -DDEBUG_SYSTEMC
#on Ubuntu
#LDFLAGS= -L$(SYSTEMC)/lib-linux64 -Wl,-rpath=$(SYSTEMC)/lib-linux64 -lsystemc -lm
#CXXFLAGS= -W -Wall -pedantic -g -I$(SYSTEMC)/include -DDEBUG_SYSTEMC

all: $(EXEC)

$(EXEC): $(OBJ) 
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


%.o: %.cpp %.h
	$(CC) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)

tar : $(HEA) $(SRC) 
	tar -cvf fft.tar makefile $^
