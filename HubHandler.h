#ifndef HUBHANDLER_H
#define HUBHANDLER_H
#include "Hub.h"
#include "Node.h"
#include <boost/thread/mutex.hpp>
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>

namespace mp3{
class HubHandler : public HubIf {
  private:
    boost::mutex m_mutex;
    boost::unordered_map<int, boost::shared_ptr<NodeIf> > nodeMap;

  public:
    HubHandler();
    ~HubHandler();
    void join(const int16_t port);
    void leave(const int16_t port);
    void getMembers(std::vector<int16_t> & _return);
};
}
#endif
