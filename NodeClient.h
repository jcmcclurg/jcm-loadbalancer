#ifndef NODECLIENT_H
#define NODECLIENT_H

#include <protocol/TBinaryProtocol.h>
#include <transport/TSocket.h>
#include <transport/TTransportUtils.h>
#include <boost/shared_ptr.hpp>
#include "Node.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace boost;

namespace mp3{
class SimpleNodeClient : public NodeClient {
  private:
    static shared_ptr<TProtocol> portToProtocol(int port){
      shared_ptr<TTransport> socket(new TSocket("localhost", port));
      socket->open();
      shared_ptr<TTransport> transport(new TFramedTransport(socket));
      return shared_ptr<TProtocol>(new TBinaryProtocol(transport));
    }

  public:
    SimpleNodeClient(int port) : NodeClient(portToProtocol(port)){
    }

    ~SimpleNodeClient(){}
};
}
#endif
