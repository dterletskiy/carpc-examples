#pragma once

#include <functional>
#include "api/service/onoff/Client.hpp"



namespace application::clients::onoff {

   class Client
      : public service::onoff::V2_0_0::Client
   {
      using tConnectedCallback = std::function< void( void ) >;

      public:
         Client( const std::string&, const std::string& name, tConnectedCallback );
         ~Client( );

      private:
         void connected( ) override;
         void disconnected( ) override;

      private:
         void response_trigger_state( const bool& ) override;
         void request_trigger_state_failed( const carpc::service::eError& ) override;
         void on_current_state( const std::string& ) override;

      public:
         void request_start( );
         carpc::comm::sequence::ID request_trigger_state( const std::string&, const std::size_t& );

      private:
         const std::string m_name = { };
         tConnectedCallback m_connected_callback;
   };

} // namespace application::clients::onoff
