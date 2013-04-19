#include "xfe.h"


DEFINE_string(host, "127.0.0.1", "Host to bind HTTP server.");
DEFINE_int32(port, 8010, "Default port.");


void response(struct evhttp_request *req, const char *output) {
  const clock_t begin_time = clock();
  
  int status = 200;
  const char *status_verb = "OK";

  const char *uri = evhttp_request_get_uri(req);
  struct evhttp_uri *decoded = NULL;

  // Decode the URI
  decoded = evhttp_uri_parse(uri);
  if (!decoded) {
    evhttp_send_error(req, HTTP_BADREQUEST, 0);
    return;
  }
  
  // TODO validate HTTP methods

  struct evbuffer *evb = evbuffer_new();
  evbuffer_add_printf(evb, output, NULL);
  evhttp_send_reply(req, status, status_verb, evb);
  evbuffer_free(evb);

  LOG(INFO) << status << ":" << evhttp_request_uri(req) << ":" <<
      float(clock() - begin_time) / CLOCKS_PER_SEC;
}

void process_home(struct evhttp_request *req, void *arg) {
  std::string output;
  ctemplate::TemplateDictionary dict("requested");

  dict["NAME"] = "Rodrigo Aliste Prieto";

  ctemplate::ExpandTemplate("templates/test.tpl", ctemplate::DO_NOT_STRIP,
    &dict, &output);
  
  response(req, output.c_str());
}

int start_http_server(int argc, char **argv) {
  std::cout << "Starting server at port " << FLAGS_port << std::endl;
  
  struct event_base *base;
  struct evhttp *http;

  base = event_base_new();
  if(base == NULL) return -1;

  http = evhttp_new(base);
  if(http == NULL) return -1;

  if(evhttp_bind_socket(http, FLAGS_host.c_str(), FLAGS_port) != 0) {
    LOG(ERROR) << "Can not bind to port " << FLAGS_port;
    return -1;
  }
  evhttp_set_cb(http, "/", process_home, argv[1]);
  //evhttp_set_gencb(http, process_request, argv[1]);
  event_base_dispatch(base);
  
  return 0;
}