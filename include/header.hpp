// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <boost/beast/version.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/core.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <nlohmann/json.hpp>
#include <boost/asio.hpp>
#include <fstream>
#include <iostream>
#include <string>

using json = nlohmann::json;
using boost::asio::ip::tcp;
namespace http = boost::beast::http;

std::string ParseInput(std::string input) {
	std::string data(input.begin()+7, input.end()-1);
	return data;
}

#endif // INCLUDE_HEADER_HPP_
