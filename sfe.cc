#include "xfe.h"

// Stats Frontend Server

int main(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);
  
  int handle = start_http_server(argc, argv);
  return handle;
}