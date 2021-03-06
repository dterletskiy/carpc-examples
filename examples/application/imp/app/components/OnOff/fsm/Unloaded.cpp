#include "imp/app/components/OnOff/fsm/Manager.hpp"
#include "imp/app/components/OnOff/fsm/Unloaded.hpp"

#include "carpc/trace/Trace.hpp"
#define CLASS_ABBR "UNLOADED"



using namespace application::components::onoff;




Unloaded::Unloaded( Manager& manager )
   : carpc::fsm::TState< Types >( eID::Unloaded, "Unloaded" )
   , m_manager( manager )
{
}

const std::optional< Types::tID > Unloaded::enter( )
{
   return eID::Loading;
}

void Unloaded::leave( )
{
}

const std::optional< Types::tID > Unloaded::process( const Types::tData& data )
{
   MSG_VRB( );
   return NoTransition;
}
