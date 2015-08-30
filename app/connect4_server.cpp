#include <iostream>
#include <string>
#include <assert.h>

#include "uv.h"

#ifndef CONNECT_4
#define CONNECT_4
#include "Connect4.h"
#endif


#define MAX_WRITE_HANDLES 1000
#define LISTEN_PORT 10060

static uv_loop_t *uv_loop;
static uv_tcp_t server;


void alloc_cb (uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    *buf = uv_buf_init((char *) malloc(suggested_size), suggested_size);
}


void on_read (uv_stream_t *tcp, ssize_t nread, const uv_buf_t *buf) {

    printf("Reading\n");
    printf("%s", tcp->data());

}


void on_connect (uv_stream_t *server_handle, int status) {

    assert((uv_tcp_t *) server_handle == &server);

    uv_tcp_t *client = new uv_tcp_t();

    uv_tcp_init(uv_loop, client);

    int r = uv_accept(server_handle, (uv_stream_t *) client);
    printf("New connection\n");

    uv_read_start((uv_stream_t *) client, alloc_cb, on_read);

}


int main (int argc, char *argv[]) {

    printf("Test\n");

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
