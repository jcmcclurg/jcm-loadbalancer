#include "HubClient.h"
#include <protocol/TBinaryProtocol.h>
#include <transport/TSocket.h>
#include <transport/TTransportUtils.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include "Hub.h"
#include "settings.h"
#include <stdlib.h>
#include <vector>

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace mp3;

using namespace boost;

int main(int argc, char** argv) {
  DEBUG("This file demonstrates what each node should do when it starts up and shuts down.");

  // Create a persistent socket to the Hub (so we can ask who is part of the group)
  shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
  shared_ptr<TTransport> transport(new TFramedTransport(socket));
  shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  HubClient hub(protocol);
  int port = 8888;

  try {
    // Register yourself with the hub
    DEBUG("Open transport");
    transport->open();
    hub.join(port);

    // Pretend to do work.
    boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
    std::vector<int16_t> m;
    DEBUG("Getting members...");
    hub.getMembers(m);
    DEBUG("Current members are:");
    for(std::vector<int16_t>::iterator iterator = m.begin(); iterator != m.end(); iterator++) {
      DEBUG("Port: " << *iterator);
    }    
    boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

    // Unregister yourself
    hub.leave(port);
    transport->close();
    DEBUG("Close transport");

  } catch (TException &tx) {
    DEBUG("Error: " << tx.what());
  }
  return 0;
}
