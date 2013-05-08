#ifndef HUBCLIENT_H
#define HUBCLIENT_H

#include <protocol/TBinaryProtocol.h>
#include <transport/TSocket.h>
#include <transport/TTransportUtils.h>
#include <boost/shared_ptr.hpp>
#include "Hub.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace boost;

namespace mp3{
class SimpleHubClient : public HubClient {
  private:
    static shared_ptr<TProtocol> portToProtocol(int port){
      shared_ptr<TTransport> socket(new TSocket("localhost", port));
      socket->open();
      shared_ptr<TTransport> transport(new TFramedTransport(socket));
      return shared_ptr<TProtocol>(new TBinaryProtocol(transport));
    }

  public:
    SimpleHubClient(int port) : HubClient(portToProtocol(port)){
    }

    ~SimpleHubClient(){}
};
}
#endif
