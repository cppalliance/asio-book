//
// Copyright (c) 2023 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//


// tag::example[]

#include <boost/asio.hpp>
namespace asio = boost::asio;

int main(int argc, char * argv[])
{
    asio::io_context ioc; // <1>
    asio::stream_file file{ioc, "./test-file", 
                           asio::stream_file::write_only | asio::stream_file::create}; // <2>

    std::string data = "Hello World\n"                           ;
    file.write(asio::buffer(data)); // <3>
    return 0;
}

// end::example[]
