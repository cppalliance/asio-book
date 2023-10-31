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
    using boost::system::error_code;
    asio::io_context ioc; 
    asio::stream_file file{ioc}; // <1>

    error_code ec;
    file.open("./test-file",  // <2>
              asio::stream_file::write_only | asio::stream_file::create, ec);

    if (!ec) // <3>
    {
        std::string data = "Hello World\n";
        file.write_some(asio::buffer(data), ec); // <4>
    }
    return ec ? EXIT_FAILURE : EXIT_SUCCESS;
}
// end::example[]

#else


#include <boost/asio.hpp>
namespace asio = boost::asio;

int main(int argc, char * argv[])
{
    using boost::system::error_code;

    // since we don't have native file support, we're using stream_descriptors directly
    asio::io_context ioc;
    asio::posix::stream_descriptor file{ioc};
    error_code ec;
    auto fd = open("./tes-file", O_WRONLY | O_CREAT);
    if (fd == -1)
        ec.assign(errno, boost::system::system_category());
    else
    {
        std::string data = "Hello World\n";
        file.write_some(asio::buffer(data), ec);
    }
    return ec ? EXIT_FAILURE : EXIT_SUCCESS;
}

#endif
