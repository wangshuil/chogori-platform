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
#include <memory>
#include <k2/common/Common.h>
#include <k2/common/Log.h>
#include "Payload.h"
#include "RPCHeader.h"
#include <iostream>

namespace k2 {
// an endpoint has: three components: protocol, IP, and port. It can be represented in a string form (url) as
// <protocol>://<ip>:<port>
// NB. we only support case-sensitive URLs, in either domainname, ipv4, or ipv6/rdma
// e.g. domain: http://google.com
//      proto=http, ip=google.com, port=0
// e.g. ipv4: tcp+k2rpc://10.0.0.1:12345
//      proto=tcp+k2rpc, ip=10.0.0.1, port=12345
// e.g. ipv6/rdma: rdma+k2rpc://[2001:db8:85a3::8a2e:370:7334]:1234567
//      proto=rdma+k2rpc, ip=2001:db8:85a3::8a2e:370:7334, port=1234567
class TXEndpoint {

public: // lifecycle
    // construct an endpoint from a url with the given allocator
    // Returns nullptr if there was a problem parsing the url
    static std::unique_ptr<TXEndpoint> fromURL(const String& url, BinaryAllocatorFunctor&& allocator);

    // default ctor
    TXEndpoint() = default;

    // default copy operator=
    TXEndpoint& operator=(const TXEndpoint&) = default;

    // default move operator=
    TXEndpoint& operator=(TXEndpoint&&) = default;

    // construct an endpoint from the tuple (protocol, ip, port) with the given allocator and protocol
    TXEndpoint(String&& protocol, String&& ip, uint32_t port, BinaryAllocatorFunctor&& allocator);

    // copy constructor
    TXEndpoint(const TXEndpoint& o);

    // move constructor
    TXEndpoint(TXEndpoint&& o);

    // destructor
    ~TXEndpoint();

public: // API

    // Comparison
    bool operator==(const TXEndpoint &other) const;

    // the stored hash value for this endpoint.
    size_t hash() const;

    // This method should be used to create new payloads. The payloads are allocated in a manner consistent
    // with the transport for the protocol of this endpoint
    std::unique_ptr<Payload> newPayload();

    // Use to determine if this endpoint can allocate
    bool canAllocate() const;

 // fields
    String url;
    String protocol;
    String ip;
    uint32_t port;

    K2_DEF_FMT(TXEndpoint, url);

private:
    size_t _hash;
    BinaryAllocatorFunctor _allocator;

}; // class TXEndpoint
} // namespace k2

// Implement std::hash for TXEndpoint so that we can use it as key in containers
namespace std {
template <>
struct hash<k2::TXEndpoint> {
size_t operator()(const k2::TXEndpoint& endpoint) const {
    return endpoint.hash();
}
}; // struct hash
} // namespace std
