#include <iostream>
#include <string>
#include <assert.h>

#include "uv.h"

#ifndef CONNECT_4
#define CONNECT_4
#include "connect4.h"
#endif

#include "connect4_helper.h"


#define MAX_WRITE_HANDLES 1024
#define LISTEN_PORT 10060

static uv_loop_t *uv_loop;
static uv_tcp_t server;


struct client_t {
  uv_tcp_t handle;
  connect4 game;
  int request_num;
};


void alloc_cb (uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    *buf = uv_buf_init((char *) malloc(suggested_size), suggested_size);
}


void on_close (uv_handle_t *handle) {

  client_t *client = (client_t *) handle->data;

  printf("Connection closed\n");

  delete client;

}


void on_read (uv_stream_t *tcp, ssize_t nread, const uv_buf_t *buf) {

    client_t *client = (client_t *) tcp->data;

    if (nread > 0) {

        printf("Reading - %s", buf->base);

        // Echoing back
        std::string res = "Received loud and clear\n";

        uv_buf_t resbuf;
        resbuf.base = (char *) res.c_str();
        resbuf.len = res.size();

        uv_write_t *writereq = new uv_write_t();
        uv_write(writereq, (uv_stream_t *) &client->handle, &resbuf, 1, NULL);

    } else {
        uv_close((uv_handle_t *) &client->handle, on_close);
    }

    free(buf->base);

}


void on_write (uv_write_t *req, int status) {
    delete req;
}


void on_connect (uv_stream_t *server_handle, int status) {

    assert((uv_tcp_t *) server_handle == &server);

    client_t *client = new client_t();

    uv_tcp_init(uv_loop, &client->handle);

    client->handle.data = client;

    int r = uv_accept(server_handle, (uv_stream_t *) &client->handle);
    printf("New connection\n");

    uv_read_start((uv_stream_t *) &client->handle, alloc_cb, on_read);

}


int main (int argc, char *argv[]) {

    uv_loop = uv_default_loop();

    int r = uv_tcp_init(uv_loop, &server);
    struct sockaddr_in address;

    r = uv_ip4_addr("0.0.0.0", LISTEN_PORT, &address);
    r = uv_tcp_bind(&server, (const struct sockaddr *) &address, 0);
    printf("Port %d bound\n", LISTEN_PORT);

    r = uv_listen((uv_stream_t *) &server, MAX_WRITE_HANDLES, on_connect);
    printf("Listening\n");

    uv_run(uv_loop, UV_RUN_DEFAULT);

    return 0;

}
