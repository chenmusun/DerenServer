/*
 * main.cpp
 *
 *  Created on: 2015年7月17日
 *      Author: chenms
 */
#include"libevent_server.h"
#include<boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
// #include<stdio.h>
namespace pt = boost::property_tree;//
INITIALIZE_EASYLOGGINGPP//初始化日志记录库

int main(int argc, char* argv[])
{
	el::Configurations conf("./log.conf");
    el::Loggers::reconfigureLogger("default", conf);
    pt::ptree tree;
    pt::read_xml("./libevent_server.xml", tree);

    int tcp_port=tree.get("server.tcpport",5678);
    int udp_port=tree.get("server.udpport",1234);
    int num_of_threads=tree.get("server.threadnum",4);
    int timespan=tree.get("server.timespan",2);
    int overtime=tree.get("server.overtime",20);

    LibeventServer ls(tcp_port,udp_port,num_of_threads,overtime,timespan);
    if(!ls.RunService())
    {
        LOG(ERROR)<<"LibeventServer fails to start service"<<std::endl;
        return -1;
    }
    LOG(INFO)<<"LibeventServer  starts with "<<num_of_threads<<" threads and tcp listen on port "<<tcp_port<<\
      "udp listen on port "<<udp_port<<" and the overtime check starts every "<<timespan<<" And the threshold is "<<overtime;
    ls.WaitForListenThread();
    LOG(ERROR)<<"LibeventServer exit"<<std::endl;
}



