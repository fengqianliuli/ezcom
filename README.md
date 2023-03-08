# ezcom

- ezcom是一个轻量化、API易用的C++通信库
- ez = easy + ZMQ

ezcom使用protobuf进行序列化，并基于ZMQ的REQ-REP通信模式进行了轻量封装。在最大化保证接口易用性的同时，保留ZMQ的高性能。

在C++领域已经有非常多性能强大、功能丰富的通信库了，为什么ezcom会诞生呢？

“库”如其名，只是为了更easy！更易用！

在我接触C++开发后，也用过不少通信库中间件，像someip协议的vsomeip，面向数据协议的fast-dds、rti-dds，boost中的aiso

它们都很好，功能强大可以适应各种场景并完成各种工作

但正是由于它们的功能过于强大，不可避免的导致API变得复杂，学习成本随之攀高


而在某些少数场景（也许是少数？也许是多数）我只想和对端通过网络完成少量的数据传输

仅仅需要保证可靠性传输（这种情况估计大多数人都直接写原生socket TCP了估计）

那么这时候就是ezcom稍微有点优势的时候了（也可能没有 ~~小声哔哔~~）

正如我一开始说的，**它的功能真的很少很少，它的API真的easy easy**

```cpp
#include <chrono>
#include <iostream>
#include <thread>

#include "message.h"
#include "requestor.h"
#include "responder.h"

void send() {
  ezcom::Requestor req("tcp://127.0.0.1:7788");
  ezcom::Message msg;
  msg.AddInt32(99);
  msg.AddString("this is test request msg");
  ezcom::Message rep = req.SyncRequest(msg);

  std::cout << "REQ ====== reply msg: " << std::endl;
  std::cout << "REQ ====== reply msg: " << rep.GetInt32(0) << std::endl;
  std::cout << "REQ ====== reply msg: " << rep.GetString(0) << std::endl;
}

void recv() {
  ezcom::Responder res("tcp://127.0.0.1:7788");
  res.StartServer([](const ezcom::Message& msg) {
    std::cout << "REP +++++++ recv msg: " << std::endl;
    std::cout << "REP +++++++ recv msg: " << msg.GetInt32(0) << std::endl;
    std::cout << "REP +++++++ recv msg: " << msg.GetString(0) << std::endl;
    ezcom::Message rep;
    rep.AddInt32(100);
    rep.AddString("this is test response reply");
    return rep;
  });

  std::this_thread::sleep_for(std::chrono::seconds(3));
}

int main(int argc, char const* argv[]) {
  std::thread t1(send);
  std::thread t2(recv);
  t1.join();
  t2.join();
  return 0;
}

```