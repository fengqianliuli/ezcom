# ezcom

- ezcom是一个轻量化、API易用的C++通信库
- ez = easy + ZMQ

ezcom使用protobuf进行序列化，并基于ZMQ的PUB-SUB通信模式进行了轻量封装。在最大化保证接口易用性的同时，保留ZMQ的高性能。

ezcom支持的通信模式
  - 同步请求，timeout机制
  - 同步请求，forgot机制
  - 异步请求

ezcom依赖：
  - protobuf v.3.20.1-rc1
  - libzmq v4.3.5
