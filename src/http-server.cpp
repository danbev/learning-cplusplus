#include "httplib.h"
#include <iostream>


int main() {
#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
    std::cout << "OpenSSL support is enabled" << std::endl;
#else
    std::cout << "OpenSSL support is not enabled" << std::endl;
#endif

    // HTTP
    httplib::Server svr;

    // HTTPS
    //httplib::SSLServer svr;

    svr.Get("/something", [](const httplib::Request &, httplib::Response &res) {
        std::cout << "/something endpoint triggerd..." << std::endl;
        res.set_content("Bajja!\n", "text/plain");
    });

    std::cout << "Server starting on 0.0.0.0:8080..." << std::endl;
    svr.listen("0.0.0.0", 8080);

    return 0;
}
