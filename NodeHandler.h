#ifndef NODEHANDLER_H
#define NODEHANDLER_H

#include "Hub.h"
#include "Node.h"
#include <boost/thread/mutex.hpp>
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/condition_variable.hpp>

namespace mp3 {

enum State {WANTED, HELD, FREE};

class NodeHandler : public NodeIf {
 private:
   boost::mutex nodeMapMutex;

   boost::unordered_map<int, boost::shared_ptr<NodeIf> > nodeMap;
   std::vector< Job > queue;
   boost::mutex queueMutex;
   boost::condition_variable queueCondition;

   boost::mutex gotReplyMutex;
   boost::condition_variable gotReplyCondition;

   boost::mutex requestQueueMutex;
   //boost::condition_variable requestQueueCondition;
   std::vector< std::pair<int,int> > requestQueue;

   int numReplied;
   int64_t lamportTimestamp;

   int myPort;
   State state;
   bool running;
   int batch_size;
   void populateQueue();

 public:
  NodeHandler();
  ~NodeHandler();
  void joinNotify(const int16_t port);
  void leaveNotify(const int16_t port);
  int16_t getNumJobs();
  void queueJob(const Job& job);
  void processJobs(std::vector<Result> & _return);
  int16_t getNumExtraJobs();
  void notifyMutexRequest(const int16_t lamportTs, const int16_t fromPort);
  void notifyMutexReply(const int16_t fromPort);
  void setBatchSize(const int16_t size);
  void giveJobs(std::vector< Job > & _return, const int16_t numJobs); 
  void shutdown();
  int getPort();
};
}
#endif
