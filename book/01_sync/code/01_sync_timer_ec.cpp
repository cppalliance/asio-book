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
    using boost::system::error_code;

    asio::io_context ioc; // <1>
    asio::steady_timer timer{ioc, std::chrono::milliseconds(50)}; // <2>

    error_code ec; // <3>
    timer.wait(ec); // <4>
    return ec ? EXIT_FAILURE : EXIT_SUCCESS;
}
// end::example[]
