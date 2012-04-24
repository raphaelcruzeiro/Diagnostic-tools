#include <stdio.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <syslog.h>
#include "comm.h"

static int init()
{
    if (!initialized) {
        CRYPTO_malloc_init();
        SSL_library_init();
        SSL_load_error_strings();
        ERR_load_BIO_strings();
        OpenSSL_add_all_algorithms();

        initialized = 1;
    }
}

int post(char *data)
{
    openlog("diagnostics_tool", LOG_NDELAY, LOG_USER);
    init();

    SSL_CTX *ctx = SSL_CTX_new(SSLv23_client_method());
    BIO *bio = BIO_new_ssl_connect(ctx);

    SSL_CTX_set_timeout(ctx, 30);

    if (!SSL_CTX_load_verify_locations(ctx, "server.crt", NULL)) {
        syslog(LOG_ERR, "Failed to load the certificate store.\n");
        BIO_free_all(bio);
        SSL_CTX_free(ctx);
        return 0;
    }

    SSL *ssl;
    BIO_get_ssl(bio, &ssl);
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

    BIO_set_conn_hostname(bio, "23.23.212.78:https");

    if(BIO_do_connect(bio) <= 0) {
        syslog(LOG_ERR, "Failed to connect.\n%s\n", ERR_reason_error_string(ERR_get_error()));
        BIO_free_all(bio);
        SSL_CTX_free(ctx);
        return 0;
    }

    if(SSL_get_verify_result(ssl) != X509_V_OK) {
        syslog(LOG_ERR, "Untrusted certificate. Aborting!");
        BIO_free_all(bio);
        SSL_CTX_free(ctx);
        return 0;
    }

    char buf[1024];
    memset(buf, 0, sizeof(buf));

    char send[2048];
    memset(send, 0, sizeof(send));

    sprintf(send, "POST / HTTP/1.1\nHost:23.23.212.78\nContent-Type:text/xml\nContent-Length:%d\n\ndata:", strlen(data) + 5);
    strcat(send, data);

    BIO_puts(bio, send);
    int res;

    while(res = BIO_read(bio, buf, sizeof(buf) -1)) {
        if (res < 0) {
            printf("Error:\n%s\n", ERR_reason_error_string(ERR_get_error()));
            BIO_free_all(bio);
            SSL_CTX_free(ctx);
            return 0;
        }

        buf[res] = 0;

        syslog(LOG_DEBUG, "%s\n", buf);
    }

    BIO_free_all(bio);
    SSL_CTX_free(ctx);

    return 1;
}
