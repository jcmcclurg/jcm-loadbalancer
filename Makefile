THRIFT_DIR=/usr/local/Cellar/thrift/0.9.0
THRIFT=$(THRIFT_DIR)/bin/thrift
CFLAGS=-I./gen-cpp -g
CXXFLAGS=-DDEBUGLEVEL=1 -I/usr/include -I./gen-cpp -I$(THRIFT_DIR)/include/thrift -I$(THRIFT_DIR)/include -Wall -Wextra -g
SRCS:=$(wildcard *.cpp)

RPCSOURCES = gen-cpp/Hub.cpp gen-cpp/node_constants.cpp gen-cpp/node_types.cpp gen-cpp/Node.cpp
RPCHEADERS := $(patsubst %.cpp,%.h,$(RPCSOURCES))
RPCOBJS := $(patsubst %.cpp,%.o,$(RPCSOURCES))
LDFLAGS=-L$(THRIFT_DIR)/lib -lpthread -lthrift -lthriftnb -levent -lboost_program_options-mt -lboost_filesystem-mt -lboost_system-mt -lboost_thread-mt

.PHONY: all clean

all: hub hubTest node nodeTest

hub: HubHandler.o $(RPCOBJS)
	$(CXX) $(CXXFLAGS)  $^ $(LDFLAGS) -o $@

hubTest: HubClient.o $(RPCOBJS)
	$(CXX) $(CXXFLAGS)  $^ $(LDFLAGS) -o $@

node: NodeHandler.o $(RPCOBJS)
	$(CXX) $(CXXFLAGS)  $^ $(LDFLAGS) -o $@

nodeTest: NodeClient.o $(RPCOBJS)
	$(CXX) $(CXXFLAGS)  $^ $(LDFLAGS) -o $@

hub.thrift: 
	$(THRIFT) -gen cpp hub.thrift

node.thrift: 
	$(THRIFT) -gen cpp node.thrift

clean:
	-rm -f *.o gen-cpp/*.o hub hubTest node nodeTest

.PHONY: thrift

thrift:
	$(THRIFT) -gen cpp hub.thrift
	$(THRIFT) -gen cpp node.thrift

.PHONY: depend
depend: .depend

.depend: $(SRCS)
	-rm -f .depend
	-$(CXX) $(CXXFLAGS) -MM $^ > .depend

include .depend
