# ezcom

- ezcom是一个轻量化、API易用的C++通信库
- ez = easy + ZMQ

ezcom使用protobuf进行序列化，并基于ZMQ的REQ-REP通信模式进行了轻量封装。在最大化保证接口易用性的同时，保留ZMQ的高性能。

ezcom支持的通信模式
  - 同步请求，timeout机制
  - 同步请求，forgot机制
  - 异步请求

ezcom依赖：
  - protobuf v.3.20.1-rc1
  - libzmq v4.3.5
  
分支情况
  - master：基于REQ-REP模式的简单Demo实现，只支持同步请求。基于PUB-SUB模式的简单Demo实现，只支持异步请求
  - v2.0_pub_sub：基于PUB-SUB模式实现同步、异步、Forgot类型的请求
  - v3.0_req_rep：基于REQ-REP模式实现同步、异步、Forgot类型的请求

在C++领域已经有非常多性能强大、功能丰富的通信库了，为什么ezcom会诞生呢？

“库”如其名，只是为了更easy！更易用！

在我接触C++开发后，也用过不少通信库中间件，像someip协议的vsomeip，面向数据协议的fast-dds、rti-dds，boost中的aiso

它们都很好，功能强大可以适应各种场景并完成各种工作

但正是由于它们的功能过于强大，不可避免的导致API变得复杂，学习成本随之攀高


而在某些少数场景（也许是少数？也许是多数）我只想和对端通过网络完成少量的数据传输

仅仅需要保证可靠性传输（这种情况估计大多数人都直接写原生socket TCP了估计）

那么这时候就是ezcom稍微有点优势的时候了（也可能没有 ~~小声哔哔~~）

正如我一开始说的，**它的功能真的很少很少，它的API真的非常easy**

**使用示例请看example，我相信大家都能非常容易的看懂！**

