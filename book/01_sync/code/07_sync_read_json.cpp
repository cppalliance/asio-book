//
// Copyright (c) 2023 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// tag::example[]
#include <boost/json.hpp>
#include <boost/asio.hpp>

namespace json = boost::json;
namespace asio = boost::asio;

template<typename Stream, typename Buffer>
json::value read_json(Stream & str, Buffer && buffer)
{
  json::stream_parser parser;

  while (!parser.done())
  {
    auto n = str.read_some(buffer.prepare(4096));
    buffer.commit(n);

    auto out = buffer.data();
    std::size_t parsed = 0u;
    for (auto itr = asio::buffer_sequence_begin(out); itr != asio::buffer_sequence_end(out); itr++)
    {
      auto n = parser.write_some(static_cast<const char*>(itr->data()), itr->size());
      parsed += n;
      if (n != itr->size())
        break;
    }
  }


  return parser.release();
}

// end::example[]

#if defined(BOOST_ASIO_HAS_FILE)

int main(int argc, char * argv[])
{
    asio::io_context ioc;
    asio::stream_file file{ioc, "./test-file", asio::stream_file::read_only};

    std::string buffer;
    auto js = read_json(file, asio::dynamic_buffer(buffer));
    return 0;
}

#else

#include <boost/asio.hpp>
namespace asio = boost::asio;

int main(int argc, char * argv[])
{
    // since we don't have native file support, we're using stream_descriptors directly
    asio::io_context ioc;
    asio::posix::stream_descriptor file{ioc, open("./test-file", O_RDONLY)};

    std::string buffer;
    auto js = read_json(file, asio::dynamic_buffer(buffer));
    return 0;
}

#endif
