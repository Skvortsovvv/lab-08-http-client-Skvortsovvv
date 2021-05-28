#include <header.hpp>
#include <iostream>

int main(int argc, char* argv[] ) {
    try
    {
        if (argc != 6 && argc != 7)
        {
            std::cerr <<
                "Usage: main <host> <port> <target> <username> <input> " <<
                "[<HTTP version: 1.0 or 1.1(default)>]\n" <<
                "Example:\n" <<
                "    http-client-sync www.example.com 80 / user hel\n" <<
                "    http-client-sync www.example.com 80 / user hel 1.0\n";
            return EXIT_FAILURE;
        }
        auto const host = argv[1];
        auto const port = argv[2];
        auto const target = argv[3];
        auto const username = argv[4];
        auto const input = argv[5];
        int version = argc == 7 && !std::strcmp("1.0", argv[6]) ? 10 : 11;

        boost::asio::io_context ioc;

        tcp::resolver resolver(ioc);
        tcp::socket socket{ ioc };

        auto address = boost::asio::ip::address::from_string(host);
        auto portNum = std::atoi(port);

        boost::asio::ip::tcp::endpoint endpoint(address, portNum);

        socket.connect(endpoint);

        http::request<http::string_body> req{ http::verb::post, target, version };
        req.set(http::field::host, host);
        req.set(http::field::user_agent, username);
        
        std::string inputjson = ParseInput(input);
        json js;
        js["input"] = inputjson;
        inputjson = js.dump(4);
        req.content_length(inputjson.size());
        req.body() = std::move(inputjson);

        http::write(socket, req);

        boost::beast::flat_buffer buffer;

        http::response<http::dynamic_body> res;

        http::read(socket, buffer, res);

        std::cout << res << std::endl;

        boost::beast::error_code ec;
        socket.shutdown(tcp::socket::shutdown_both, ec);

        if (ec && ec != boost::beast::errc::not_connected)
            throw boost::beast::system_error{ ec };
    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
