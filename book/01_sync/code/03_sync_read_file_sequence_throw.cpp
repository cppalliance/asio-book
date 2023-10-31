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

    std::string data1, data2;
    data1.resize(512); // <2>
    data2.resize(512);

    std::array<asio::mutable_buffer, 2u> seq {asio::buffer(data1), asio::buffer(data2)};

    std::size_t n = file.read_some(seq); // <3>
    if (n <= data1.size()) // <4>
    {
        data1.resize(n);
        data2.clear();
    }
    else
        data2.resize(n - data1.size());
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

    std::string data1, data2;
    data1.resize(512);
    data2.resize(512);

    std::array<asio::mutable_buffer, 2u> seq {asio::buffer(data1), asio::buffer(data2)};

    std::size_t n = file.read_some(seq);
    if (n <= data1.size())
    {
        data1.resize(n);
        data2.clear();
    }
    else
        data2.resize(n - data1.size());
    return 0;
}

#endif
