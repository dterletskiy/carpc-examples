#pragma once

#include "api/service/onoff/Server.hpp"



namespace symbiont::interface::onoff {

   class Server
      : public service::onoff::V2_0_0::Server
   {
      public:
         Server( );
         ~Server( );

      private:
         void connected( ) override;
         void disconnected( ) override;

      public:
         void request_start( ) override;
         void request_trigger_state( const std::string&, const std::size_t& ) override;
   };

} // namespace symbiont::interface::onoff
