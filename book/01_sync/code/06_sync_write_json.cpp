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

template<typename Stream>
void write_json(Stream & str, const json::value & value)
{
  json::serializer ser;
  ser.reset(&value); // <1>

  std::string memory;
  memory.reserve(8192);
  auto buf = asio::dynamic_buffer(memory); // <2>

  while (!ser.done())
  {
    asio::mutable_buffer rd = buf.prepare(4096); // <3>
    auto n = ser.read(static_cast<char*>(rd.data()), rd.size()).size(); // <4>
    buf.commit(n); // <5>
    n = str.write_some(buf.data()); // <6>
    buf.consume(n); // <7>
  }

  if (buf.size() > 0u)
    asio::write(str, buf.data()); // <8>
}

// end::example[]

#if defined(BOOST_ASIO_HAS_FILE)

int main(int argc, char * argv[])
{
    asio::io_context ioc;
    asio::stream_file file{ioc, "./test-file", 
                           asio::stream_file::write_only | asio::stream_file::create};

    json::value data = {{"greeting", "Hello"}, {"who", "World"}};
    write_json(file, data);
    return 0;
}

#else

#include <boost/asio.hpp>
namespace asio = boost::asio;

int main(int argc, char * argv[])
{
    // since we don't have native file support, we're using stream_descriptors directly
    asio::io_context ioc;
    asio::posix::stream_descriptor file{ioc, open("./test-file", O_WRONLY | O_CREAT)};

    json::value data = {{"greeting", "Hello"}, {"who", "World"}};
    write_json(file, data);
    return 0;
}

#endif
