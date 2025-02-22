/*
MIT License

Copyright(c) 2020 Futurewei Cloud

    Permission is hereby granted,
    free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

    The above copyright notice and this permission notice shall be included in all copies
    or
    substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS",
    WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
    DAMAGES OR OTHER
    LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#pragma once
#include <k2/appbase/Appbase.h>
#include <k2/appbase/AppEssentials.h>
#include <k2/persistence/plog_client/PlogClient.h>

using namespace k2;
namespace k2::log {
inline thread_local k2::logging::Logger ptest("k2::ptest");
}
class PlogTest {
public:  // application lifespan
    PlogTest();
    ~PlogTest();

    // required for seastar::distributed interface
    seastar::future<> gracefulStop();
    seastar::future<> start();

    seastar::future<> runTest1();
    seastar::future<> runTest2();
    seastar::future<> runTest3();

private:
    int exitcode = -1;
    std::unique_ptr<k2::TXEndpoint> _cpoEndpoint;
    k2::PlogClient _client;
    k2::ConfigVar<std::vector<k2::String>> _plogConfigEps{"plog_server_endpoints"};
    seastar::future<> _testFuture = seastar::make_ready_future();
    seastar::timer<> _testTimer;

    k2::String _plogId;
};
