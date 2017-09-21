/*
 * =====================================================================================
 *
 *       Filename:  boost_socket.h
 *
 *    Description:  A socket using boost libraries.
 *
 *        Version:  1.0
 *        Created:  12/03/2016 04:27:41 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dilawar Singh (), dilawars@ncbs.res.in
 *   Organization:  NCBS Bangalore
 *
 * =====================================================================================
 */

#ifndef  boost_socket_INC
#define  boost_socket_INC

#include <cstdio>
#include <iostream>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#if defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)

using boost::asio::local::stream_protocol;

class session
  : public boost::enable_shared_from_this<session>
{
public:
  session(boost::asio::io_service& io_service)
    : socket_(io_service)
  {
  }

  stream_protocol::socket& socket()
  {
    return socket_;
  }

  void start()
  {
    socket_.async_read_some(boost::asio::buffer(data_),
        boost::bind(&session::handle_read,
          shared_from_this(),
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

  void handle_read(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    if (!error)
    {
      boost::asio::async_write(socket_,
          boost::asio::buffer(data_, bytes_transferred),
          boost::bind(&session::handle_write,
            shared_from_this(),
            boost::asio::placeholders::error));
    }
  }

  void handle_write(const boost::system::error_code& error)
  {
    if (!error)
    {
      socket_.async_read_some(boost::asio::buffer(data_),
          boost::bind(&session::handle_read,
            shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
  }

private:
  // The socket used to communicate with the client.
  stream_protocol::socket socket_;

  // Buffer used to store data received from the client.
  boost::array<char, 1024> data_;
};

typedef boost::shared_ptr<session> session_ptr;

class server
{
public:
  server(boost::asio::io_service& io_service, const std::string& file)
    : io_service_(io_service),
      acceptor_(io_service, stream_protocol::endpoint(file))
  {
    session_ptr new_session(new session(io_service_));
    acceptor_.async_accept(new_session->socket(),
        boost::bind(&server::handle_accept, this, new_session,
          boost::asio::placeholders::error));
  }

  void handle_accept(session_ptr new_session,
      const boost::system::error_code& error)
  {
    if (!error)
    {
      new_session->start();
      new_session.reset(new session(io_service_));
      acceptor_.async_accept(new_session->socket(),
          boost::bind(&server::handle_accept, this, new_session,
            boost::asio::placeholders::error));
    }
  }

private:
  boost::asio::io_service& io_service_;
  stream_protocol::acceptor acceptor_;
};



#else // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
# error Local sockets not available on this platform.
#endif // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
 

#endif   /* ----- #ifndef boost_socket_INC  ----- */
