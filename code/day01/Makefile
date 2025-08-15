# Windows Makefile for day01 socket example
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

all: server client

server: server_fixed.cpp
	$(CXX) $(CXXFLAGS) server_fixed.cpp -o server -lws2_32

client: client_fixed.cpp
	$(CXX) $(CXXFLAGS) client_fixed.cpp -o client -lws2_32

clean:
	del server.exe client.exe 2>NUL || true

.PHONY: all clean
