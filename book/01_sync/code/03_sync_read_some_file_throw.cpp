//
// Copyright (c) 2023 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/asio/basic_file.hpp>
#if defined(BOOST_ASIO_HAS_FILE)

// tag::example[]
#include <boost/asio.hpp>
namespace asio = boost::asio;

int main(int argc, char * argv[])
{
    asio::io_context ioc;
    asio::stream_file file{ioc, "./test-file", asio::stream_file::read_only}; // <1>

    std::string data;
    data.resize(1024); // <2>
    std::size_t n = file.read_some(asio::buffer(data)); // <3>
    data.resize(n); // <4>
    return 0;
}
// end::example[]

#else

#include <boost/asio.hpp>
namespace asio = boost::asio;

int main(int argc, char * argv[])
{
    // since we don't have native file support, we're using stream_descriptors directly
    asio::io_context ioc;
    asio::posix::stream_descriptor file{ioc, open("./test-file", O_RDONLY)};

    std::string data;
    data.resize(1024);
    std::size_t n = file.read_some(asio::buffer(data));
    data.resize(n); // <5>
    return 0;
}

#endif
