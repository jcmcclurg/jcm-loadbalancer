#include "Node.h"
#include "Hub.h"
#include <protocol/TBinaryProtocol.h>
#include <transport/TSocket.h>
#include <transport/TTransportUtils.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include "NodeClient.h"
#include "HubClient.h"
#include "settings.h"
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace mp3;

using namespace boost;

int main(int argc, char** argv) {
  srand (time(NULL));
  DEBUG("This file demonstrates what a transaction with a node should look like.");

  // Connect to the node

  try {
    DEBUG("Getting node list.");
    boost::shared_ptr<HubIf> hub(new SimpleHubClient(9090));  
    std::vector<int16_t> m;
    hub->getMembers(m);

    DEBUG("Connecting to node " << m[0] << ".");
    boost::shared_ptr<NodeIf> node(new SimpleNodeClient(m[0]));
    
    int c = 0;
    while(true){
      DEBUG("Enqueueing job " << c);
      Job j;
      j.id = c;
      j.hopcount = 0;
      node->queueJob(j);
      boost::this_thread::sleep(boost::posix_time::milliseconds(rand() % 500));
      c++;
    }
    DEBUG("Client exits.");


  } catch (TException &tx) {
    printf("ERROR: %s\n", tx.what());
  }
  return 0;
}
