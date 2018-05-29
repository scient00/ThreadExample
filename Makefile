################  COMPILE FLAG ########################
GXX := g++
#GXX := icpc
TARGET = ./run/threadExample
CPPFLAGS = -Wall -O2 -fPIC -std=c++11 

INCLUDE=-I"./include" 

SOURCE=./source

LDFLAGS= -lpthread
	

OBJS=$(patsubst %.cpp, %.o, $(wildcard ./source/*.cpp))

$(TARGET):$(OBJS)
	$(GXX) $(CPPFLAGS) -o $@ $(OBJS) $(LDFLAGS)

$(OBJS):%.o:%.cpp
	$(GXX) $(CPPFLAGS) -c -g -DLINUX $< $(INCLUDE) -o $@

clean:
	rm -f *.o *.d $(TARGET)
	rm -f $(SOURCE)/*.o

.PHONY: all clean
