#include <ctime>
#include <iostream>
#include <cstring>

#include <evhttp.h>

#include <glog/logging.h>
#include <gflags/gflags.h>
#include <ctemplate/template.h>

#ifndef XFE_H_
#define XFE_H_
void process_request(struct evhttp_request *req, void *arg);
int start_http_server(int argc, char **argv);
#endif   // XFE_H_