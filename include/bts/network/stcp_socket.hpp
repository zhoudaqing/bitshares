#pragma once
#include <fc/network/tcp_socket.hpp>
#include <fc/crypto/blowfish.hpp>
#include <fc/crypto/elliptic.hpp>

namespace bts {  namespace network {

/**
 *  Uses ECDH to negotiate a blowfish key for communicating
 *  with other nodes on the network.
 */
class stcp_socket : public virtual fc::iostream
{
  public:
    stcp_socket();
    ~stcp_socket();
    fc::tcp_socket&  get_socket() { return _sock; }
    void             accept();

    void             connect_to( const fc::ip::endpoint& ep );

    virtual size_t   readsome( char* buffer, size_t max );
    virtual bool     eof()const;

    virtual size_t   writesome( const char* buffer, size_t len );
    virtual void     flush();
    virtual void     close();

  private:
    fc::ecc::private_key _priv_key;
    fc::tcp_socket _sock;
    fc::blowfish   _send_bf;
    fc::blowfish   _recv_bf;
};

typedef std::shared_ptr<stcp_socket> stcp_socket_ptr;

} } // bts::network
