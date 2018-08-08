.SUFFIXES:
.SUFFIXES: .c .cpp

CC = gcc
GCC = g++

.c:
	$(CC) -I$(INCDIR) $(CFLAGS) $< $(GL_LIBS) -o $@

.cpp:
	$(GCC) -Wall -Wunused -std=c++11 -O2 `pkg-config --cflags opencv` Vision.cpp SOM.cpp Sample.cpp CSVReader.cpp DataSet.cpp Node.cpp Test.cpp RasBot.cpp tcp_client.cpp $< -o $@ `pkg-config --libs opencv` -laruco -lcurl
