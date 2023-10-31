//
// Copyright (c) 2023 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/asio/basic_file.hpp>
#if defined(BOOST_ASIO_HAS_FILE)

// tag::example[]
#include <array>

#include <boost/asio.hpp>
namespace asio = boost::asio;

int main(int argc, char * argv[])
{
    asio::io_context ioc;
    asio::stream_file file{ioc, "./test-file", 
                           asio::stream_file::write_only | asio::stream_file::create};

    std::string header = "Hello ";
    std::string body = "World!\n";

    std::array<asio::const_buffer, 2u> buffers = {asio::buffer(header), asio::buffer(body)}; // <1>
    asio::write(file, buffers); // <2>
    return 0;
}
// end::example[]

#else
#include <array>

#include <boost/asio.hpp>
namespace asio = boost::asio;

int main(int argc, char * argv[])
{
  // since we don't have native file support, we're using stream_descriptors directly
  asio::io_context ioc;
  asio::posix::stream_descriptor file{ioc, open("./test-file", O_WRONLY | O_CREAT)};


  std::string header = "Hello ";
  std::string body = "World!\n";

  std::array<asio::const_buffer, 2u> buffers = {asio::buffer(header), asio::buffer(body)}; // <1>
  asio::write(file, buffers); // <2>
  return 0;
}

#endif
