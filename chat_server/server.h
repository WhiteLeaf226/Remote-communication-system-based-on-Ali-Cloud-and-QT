#ifndef __SERVER_H__
#define __SERVER_H__

#include <event.h>
#include <event2/listener.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include "chatlist.h"
#include <jsoncpp/json/json.h>
#include <unistd.h>
#include <iostream>

using namespace std;

#define IP		"172.16.200.246"
#define PORT	10010
#define MAXSIZE 256 *1024

class Server
{

public:
	Server(const char *ip = "127.0.0.1", int port = 10010);
	~Server();
private:
	//事件 客户端文件描述符 客户端地址 地址大小  传入参数
	//evconnlistener对象回调函数
	static void listener_cb(struct evconnlistener *listener, 
			evutil_socket_t fd, struct sockaddr *addr, 
			int socklen, void *arg);
	//用户线程调用函数
	static void client_handler(int fd);
	//文件线程调用函数
	static void send_flie_handler(int, int, int*, int*);
	//接收数据
	static void read_cb(struct bufferevent *bev, void *ctx);
	//异常
	static void event_cb(struct bufferevent *bev,
			short what, void *ctx);
	//用户注册
	static void server_register(struct bufferevent *bev,
			Json::Value val);
	//用户登入
	static void server_login(struct bufferevent *bev, 
			Json::Value val);
	//添加好友
	static void server_add_friend(struct bufferevent *bev, 
			Json::Value val);
	//创建群
	static void server_create_group(struct bufferevent *bev, 
			Json::Value val);
	//添加群
	static void server_add_group(struct bufferevent *bev, 
			Json::Value val);
	//私聊
	static void server_private_chat(struct bufferevent *bev, 
			Json::Value val);
	//群聊
	static void server_group_chat(struct bufferevent *bev, 
			Json::Value val);
	//获取群成员
	static void server_get_group_member(struct bufferevent *bev,
			Json::Value val);
	//用户下线
	static void server_user_offline(struct bufferevent *bev,
			Json::Value val);
	//发送文件
	static void server_send_file(struct bufferevent *bev,
			Json::Value val);

private:
	struct event_base *base;  //事件集合
	struct evconnlistener *listener;  //监听事件
	static ChatInfo *chatlist;  //链表对象
	static ChatDataBase *chatdb;
};


#endif
