

#include "server_http.hpp"

// 文件
#include <boost/filesystem.hpp>

// json
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <future>
#include <iostream>
#include <thread>

// server
using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

// json
using namespace boost::property_tree;

// 注册 url
void register_path(HttpServer &server) {
}

int main(int argc, char **argv) {


  // 用一个线程监听 8080 端口
  HttpServer server;
  server.config.port = 8080;
  register_path(server);

  std::promise<unsigned short> server_port;
  std::thread server_thread([&server, &server_port](unsigned short port) {
    server.start([&server_port](unsigned short port) {
      server_port.set_value(port);
    });
  });

  std::cout << "Server listening on port " << server_port.get_future().get() << std::endl;

  server_thread.join();

  return 0;
}
