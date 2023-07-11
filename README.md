# EZcom
![https://en.cppreference.com/w/cpp/14](https://img.shields.io/badge/language-C%2B%2B14-brightgreen)
![https://xmake.io/#/zh-cn/](https://img.shields.io/badge/xmake-v2.7.9-blue)
![Static Badge](https://img.shields.io/badge/license-Apache2.0-yellow?link=https%3A%2F%2Fxmake.io%2F%23%2Fzh-cn%2F)


## 概述

- EZcom是一个轻量化、API易用的C++通信库
- EZ = Easy + ZMQ

EZcom依赖：
  - protobuf v.3.20.1-rc1
  - libzmq v4.3.5

EZcom使用protobuf进行序列化，底层封装了ZMQ进行通信，并原生支持ZMQ的IPC和TCP通信模式
- 支持跨域、跨设备tcp网络通信
- client-server模式下支持connect回调获取当前连接状态
- 支持的通信模式
  - 同步消息请求/超时机制
  - 异步消息请求/超时机制
  - 发布消息模式/topic机制
  - 订阅消息模式/topic机制
- 支持基本数据类型的自动序列化
  - int32
  - int64
  - uint32
  - uint64
  - float
  - double
  - bool
  - string
- 支持用户自定义数据结构的强制序列化，利用reinterpret_cast强制转换。需要两端字节对齐

## 安装
### Linux
#### 环境安装

```bash
sudo add-apt-repository ppa:xmake-io/xmake
sudo apt update && sudo apt upgrade
sudo apt install gcc g++ make xmake libtool autoconf
```

#### 依赖安装

ZMQ源码安装
```bash
git clone https://github.com/zeromq/libzmq.git
cd libzmq
./autogen.sh
./configure
make -j8
sudo make install
sudo ldconfig
```

protobuf源码安装
```bash
git clone https://github.com/protocolbuffers/protobuf.git
cd protobuf
git checkout v3.20.1-rc1
./autogen.sh
./configure
make -j8
sudo make install
sudo ldconfig
```

#### EZcom安装

```bash
git clone https://github.com/fengqianliuli/ezcom.git
cd ezcom
git checkout v4.0
xmake -j8
xmake install
```

## 示例（待补充）

