// Framework
#include "carpc/application/main.hpp"



const carpc::application::Thread::Configuration::tVector services = { };



#include <bitset>
#include "carpc/common/IPC.hpp"
#include "carpc/helpers/functions/print.hpp"
#include "api/stream/sensor.pb.h"

#if 0
namespace test_stream {

   struct Data
   {
      Data( ) = default;

      Data( const std::size_t& id, const std::string& name )
         : m_id( id )
         , m_name( name )
      {
      }

      bool to_stream( carpc::ipc::tStream& stream ) const
      {
         return carpc::ipc::serialize( stream, m_id, m_name );
      }
      bool from_stream( carpc::ipc::tStream& stream )
      {
         return carpc::ipc::deserialize( stream, m_id, m_name );
      }

      void print( ) const
      {
         MSG_DBG( "id: 0x%X / name: %s", m_id, m_name.c_str( ) );
      }

      const std::size_t& id( ) const
      {
         return m_id;
      }

      const std::string& name( ) const
      {
         return m_name;
      }

      std::size_t m_id = 0xFFFFFFFF;
      std::string m_name = "NoName";
   };

   bool operator==( const Data& data_1, const Data data_2 )
   {
      return data_1.id( ) == data_2.id( ) && data_1.name( ) == data_2.name( );
   }



   bool operator==( const sensor::Data& data_1, const sensor::Data data_2 )
   {
      return data_1.id( ) == data_2.id( ) && data_1.name( ) == data_2.name( );
   }



   #define TEST( A, B ) \
      if( A == B ) \
      { \
         MSG_DBG( "%s == %s", #A, #B ); \
      } \
      else \
      { \
         MSG_ERR( "%s != %s", #A, #B ); \
      }






   void run( )
   {
      carpc::ipc::tStream stream;



      if( false )
      {
         bool                       value_bool = true,                        test_value_bool = false;
         std::uint8_t               value_uint8_t = 0xAB,                     test_value_uint8_t = 0;
         std::int16_t               value_int16_t = -12345,                   test_value_int16_t = 0;
         float                      value_float = 123.456,                    test_value_float = 0.0;
         double                     value_double = -654.321,                  test_value_double = -0.0;
         std::vector< int >         value_vector_int = { 11, 22, 33 },        test_value_vector_int = { 0 };
         std::set< int >            value_set_int = { 44, 55, 66 },           test_value_set_int = { 0 };
         std::optional< double >    value_optional_double = 987.654,          test_value_optional_double = std::nullopt;
         std::optional< long >      value_optional_long = std::nullopt,       test_value_optional_long = 123456789;
         std::string                value_string = "Hello CARPC",             test_value_string = { };
         Data                       value_data{ 0xABCDEF, "DATA" },           test_value_data{ 0, "" };
         sensor::Data               value_sensor_data,                        test_value_sensor_data;
         value_sensor_data.set_id( 0xAABBCCDD );
         value_sensor_data.set_name( "GPB_DATA" );
         std::shared_ptr< Data > p_value_data = std::make_shared< Data >( 0xABCDEF, "SHARED" );
         std::shared_ptr< Data > p_value_data_test = nullptr;//std::make_shared< Data >( 0x12345678, "NoName" );

         std::map<
               std::size_t,
               std::map<
                  std::size_t,
                  std::vector< std::optional< std::set< double > > >
               >
         > value =
         {
            {
               100,
               {
                  { 11111, std::vector< std::optional< std::set< double > > >{ std::set< double >{ 1.1, 2.2, 3.3 } } },
                  { 22222, std::vector< std::optional< std::set< double > > >{ std::set< double >{ 4.4, 5.5, 6.6 } } },
                  { 33333, std::vector< std::optional< std::set< double > > >{ std::nullopt } }
               }
            },
            {
               200,
               {
                  { 44444, std::vector< std::optional< std::set< double > > >{ std::nullopt } },
                  { 55555, std::vector< std::optional< std::set< double > > >{ std::set< double >{ 7.7, 8.8, 9.9 } } },
                  { 66666, std::vector< std::optional< std::set< double > > >
                     {
                        std::set< double >{ 1.0, 2.0, 3.0 }, std::nullopt, std::nullopt
                     }
                  },
               }
            },
         }, test_value;

         carpc::ipc::serialize(
                 stream
               , value_bool
               , value_uint8_t
               , value_int16_t
               , value_float
               , value_double
               , value_vector_int
               , value_set_int
               , value_optional_double
               , value_optional_long
               , value_string
               , value_data
               , value_sensor_data
               , value
               , p_value_data
            );

         carpc::ipc::deserialize(
                 stream
               , test_value_bool
               , test_value_uint8_t
               , test_value_int16_t
               , test_value_float
               , test_value_double
               , test_value_vector_int
               , test_value_set_int
               , test_value_optional_double
               , test_value_optional_long
               , test_value_string
               , test_value_data
               , test_value_sensor_data
               , test_value
               , p_value_data_test
            );

         TEST( value_bool, test_value_bool );
         TEST( value_uint8_t, test_value_uint8_t );
         TEST( value_int16_t, test_value_int16_t );
         TEST( value_float, test_value_float );
         TEST( value_double, test_value_double );
         TEST( value_vector_int, test_value_vector_int );
         TEST( value_set_int, test_value_set_int );
         TEST( value_optional_double, test_value_optional_double );
         TEST( value_optional_long, test_value_optional_long );
         TEST( value_string, test_value_string );
         TEST( value_data, test_value_data );
         TEST( value_sensor_data, test_value_sensor_data );
         TEST( value, test_value );

         if( nullptr != p_value_data )
         {
            p_value_data->print( );
         }
         else
         {
            MSG_DBG( "p_value_data = nullptr" );
         }
         if( nullptr != p_value_data_test )
         {
            p_value_data_test->print( );
         }
         else
         {
            MSG_DBG( "p_value_data_test = nullptr" );
         }
      }

      if( false )
      {
         std::shared_ptr< Data > p_value_data = std::make_shared< Data >( 0xABCDEF, "SHARED" );
         std::shared_ptr< Data > p_value_data_test = nullptr;//std::make_shared< Data >( 0x12345678, "NoName" );
         if( nullptr != p_value_data )
         {
            p_value_data->print( );
         }
         else
         {
            MSG_DBG( "p_value_data = nullptr" );
         }
         if( nullptr != p_value_data_test )
         {
            p_value_data_test->print( );
         }
         else
         {
            MSG_DBG( "p_value_data_test = nullptr" );
         }

         carpc::ipc::serialize( stream, p_value_data );

         carpc::ipc::deserialize( stream, p_value_data_test );

         if( nullptr != p_value_data )
         {
            p_value_data->print( );
         }
         else
         {
            MSG_DBG( "p_value_data = nullptr" );
         }
         if( nullptr != p_value_data_test )
         {
            p_value_data_test->print( );
         }
         else
         {
            MSG_DBG( "p_value_data_test = nullptr" );
         }
      }

      if( false )
      {
         std::unique_ptr< Data > p_value_data = std::make_unique< Data >( 0xABCDEF, "UNIQUE" );
         std::unique_ptr< Data > p_value_data_test = nullptr;//std::make_unique< Data >( 0x12345678, "NoName" );
         if( nullptr != p_value_data )
         {
            p_value_data->print( );
         }
         else
         {
            MSG_DBG( "p_value_data = nullptr" );
         }
         if( nullptr != p_value_data_test )
         {
            p_value_data_test->print( );
         }
         else
         {
            MSG_DBG( "p_value_data_test = nullptr" );
         }

         carpc::ipc::serialize( stream, p_value_data );

         carpc::ipc::deserialize( stream, p_value_data_test );

         if( nullptr != p_value_data )
         {
            p_value_data->print( );
         }
         else
         {
            MSG_DBG( "p_value_data = nullptr" );
         }
         if( nullptr != p_value_data_test )
         {
            p_value_data_test->print( );
         }
         else
         {
            MSG_DBG( "p_value_data_test = nullptr" );
         }
      }

   }

} // namespace test_stream
#endif



#include <json/reader.h>

#if 0
namespace test_jsoncpp {

} // namespace test_jsoncpp
#endif



#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

#if 0
namespace test_nlohmann_json {

   struct Area
   {
      std::string    name;
      int32_t        id;
   };

   struct Areas
   {
      std::vector< Area >  areas;
      std::string          operation;
   };

   struct VissProperty
   {
      std::string    name;
   };

   struct AreaMapping
   {
      Areas          areas_combination;
      VissProperty   viss_property;
   };

   struct Property
   {
      std::string    name;
      int32_t        id;
   };

   struct Value
   {
      std::string                   type;
      std::vector< std::string >    initial;
      std::string                   min;
      std::string                   max;
   };

   struct MappingElement
   {
      std::string                description;
      std::string                area_type;
      Property                   property;
      std::string                access_mode;
      std::string                change_mode;
      Value                      value;
      std::vector< AreaMapping > area_mapping;
   };

   struct Root
   {
      void dump( )
      {
         MSG_DBG( "elements: %zu", mapping_elements.size( ) );
         for( auto mapping_element : mapping_elements )
         {
            MSG_DBG( "description: %s", mapping_element.description.c_str( ) );
            MSG_DBG( "area_type: %s", mapping_element.area_type.c_str( ) );
            MSG_DBG( "property:" );
            MSG_DBG( "   name: %s", mapping_element.property.name.c_str( ) );
            MSG_DBG( "   id: %d", mapping_element.property.id );
            MSG_DBG( "access_mode: %s", mapping_element.access_mode.c_str( ) );
            MSG_DBG( "change_mode: %s", mapping_element.change_mode.c_str( ) );
            MSG_DBG( "value:" );
            MSG_DBG( "   type: %s", mapping_element.value.type.c_str( ) );
            MSG_DBG( "   min: %s", mapping_element.value.min.c_str( ) );
            MSG_DBG( "   max: %s", mapping_element.value.max.c_str( ) );
            MSG_DBG( "   initial:" );
            for( const auto& initial : mapping_element.value.initial )
               MSG_DBG( "      %s", initial.c_str( ) );
            MSG_DBG( "area_mapping:" );
            for( const auto& mapping : mapping_element.area_mapping )
            {
               MSG_DBG( "   areas_combination:" );
               MSG_DBG( "     operation: %s", mapping.areas_combination.operation.c_str( ) );
               for( const auto& area : mapping.areas_combination.areas )
               {
                  MSG_DBG( "     area:" );
                  MSG_DBG( "        name: %s", area.name.c_str( ) );
                  MSG_DBG( "        name: %d", area.id );
               }
               MSG_DBG( "   viss_property:" );
               MSG_DBG( "      name: %s", mapping.viss_property.name.c_str( ) );
            }
         }
      }
      std::vector< MappingElement > mapping_elements;
   };



   #define FROM_JSON_ALL( JSON_OBJECT, JSON_ATTR_NAME, FIELD_NAME ) \
   { \
      MSG_DBG( "JSON_ATTR_NAME: %s", JSON_ATTR_NAME ); \
      MSG_DBG( "JSON_OBJECT: %s", JSON_OBJECT.dump( ).c_str( ) ); \
      auto foundElement = JSON_OBJECT.find( JSON_ATTR_NAME ); \
      if( JSON_OBJECT.end( ) != foundElement && false == foundElement->empty( ) ) \
      { \
         MSG_DBG( "foundElement: %s", foundElement->dump( ).c_str( ) ); \
         foundElement->get_to( FIELD_NAME ); \
      } \
   }

   #define FROM_JSON( JSON_OBJECT, JSON_ATTR_NAME, FIELD_NAME ) \
   { \
      MSG_DBG( "JSON_ATTR_NAME: %s", JSON_ATTR_NAME ); \
      auto foundElement = JSON_OBJECT.find( JSON_ATTR_NAME ); \
      if( JSON_OBJECT.end( ) != foundElement && false == foundElement->empty( ) ) \
      { \
         foundElement->get_to( FIELD_NAME ); \
      } \
   }



   // Area
   void to_json( nlohmann::json& j, const Area& val )
   {
      j = nlohmann::json
      {
         { "name", val.name },
         { "id", val.id }
      };
   }
   void from_json( const nlohmann::json& j, Area& val )
   {
      FROM_JSON( j, "name", val.name );
      FROM_JSON( j, "id", val.id );
   }

   // Areas
   void to_json( nlohmann::json& j, const Areas& val )
   {
      j = nlohmann::json
      {
         { "areas", val.areas },
         { "operation", val.operation }
      };
   }
   void from_json( const nlohmann::json& j, Areas& val )
   {
      FROM_JSON( j, "areas", val.areas );
      FROM_JSON( j, "operation", val.operation );
   }

   // VissProperty
   void to_json( nlohmann::json& j, const VissProperty& val )
   {
      j = nlohmann::json
      {
         { "name", val.name }
      };
   }
   void from_json( const nlohmann::json& j, VissProperty& val )
   {
      FROM_JSON( j, "name", val.name );
   }

   // AreaMapping
   void to_json( nlohmann::json& j, const AreaMapping& val )
   {
      j = nlohmann::json
      {
         { "areas_combination", val.areas_combination },
         { "viss_property", val.viss_property }
      };
   }
   void from_json( const nlohmann::json& j, AreaMapping& val )
   {
      FROM_JSON( j, "areas_combination", val.areas_combination );
      FROM_JSON( j, "viss_property", val.viss_property );
   }

   // Property
   void to_json( nlohmann::json& j, const Property& val )
   {
      j = nlohmann::json
      {
         { "name", val.name },
         { "id", val.id }
      };
   }
   void from_json( const nlohmann::json& j, Property& val )
   {
      FROM_JSON( j, "name", val.name );
      FROM_JSON( j, "id", val.id );
   }

   // Value
   void to_json( nlohmann::json& j, const Value& val )
   {
      j = nlohmann::json
      {
         { "type", val.type },
         { "initial", val.initial },
         { "min", val.min },
         { "max", val.max }
      };
   }
   void from_json( const nlohmann::json& j, Value& val )
   {
      FROM_JSON( j, "type", val.type );
      FROM_JSON( j, "initial", val.initial );
      FROM_JSON( j, "min", val.min );
      FROM_JSON( j, "max", val.max );
   }

   // MappingElement
   void to_json( nlohmann::json& j, const MappingElement& val )
   {
      j = nlohmann::json
      {
         { "description", val.description },
         { "area_type", val.area_type },
         { "property", val.property },
         { "access_mode", val.access_mode },
         { "change_mode", val.change_mode },
         { "value", val.value },
         { "area_mapping", val.area_mapping }
      };
   }
   void from_json( const nlohmann::json& j, MappingElement& val )
   {
      FROM_JSON( j, "description", val.description );
      FROM_JSON( j, "area_type", val.area_type );
      FROM_JSON( j, "property", val.property );
      FROM_JSON( j, "access_mode", val.access_mode );
      FROM_JSON( j, "change_mode", val.change_mode );
      FROM_JSON( j, "value", val.value );
      FROM_JSON( j, "area_mapping", val.area_mapping );
   }

   // Root
   void to_json( nlohmann::json& j, const Root& val )
   {
      j = nlohmann::json
      {
         { "mapping_elements", val.mapping_elements }
      };
   }
   void from_json( const nlohmann::json& j, Root& val )
   {
      FROM_JSON( j, "mapping_elements", val.mapping_elements );
   }



   bool parse_to_cpp( const std::string& json, Root& root, std::string& error )
   {
      bool result = false;

      try
      {
         nlohmann::json j_filtered = nlohmann::json::parse( json );
         // std::cout << std::setw(4) << j_filtered << std::endl;
         root = j_filtered.get< Root >( );
         result = true;
      }
      catch( nlohmann::json::exception& e )
      {
         result = false;
         error = e.what( );
         MSG_ERR( "error: %s", error.c_str( ) );
      }

      if( result )
         root.dump( );

      return result;
   }

   const char* const to_string( const nlohmann::json::parse_event_t& event )
   {
      switch( event )
      {
         case nlohmann::json::parse_event_t::object_start:  return "object_start";
         case nlohmann::json::parse_event_t::object_end:    return "object_end";
         case nlohmann::json::parse_event_t::array_start:   return "array_start";
         case nlohmann::json::parse_event_t::array_end:     return "array_end";
         case nlohmann::json::parse_event_t::key:           return "key";
         case nlohmann::json::parse_event_t::value:         return "value";
         default:                                           return "undefined";
      }
      return "undefined";
   }

   bool parse( const std::string& json, std::string& error )
   {
      bool result = false;

      try
      {
         nlohmann::json::parser_callback_t cb = [ ]( int depth, nlohmann::json::parse_event_t event, nlohmann::json& parsed )
         {
            MSG_DBG( "event: '%s' / parsed: '%s'", to_string( event ), parsed.dump( ).c_str( ) );
            return true;
         };

         nlohmann::json j_filtered = nlohmann::json::parse( json, cb, false );
         // std::cout << std::setw(4) << j_filtered << std::endl;

         result = true;
      }
      catch( nlohmann::json::exception& e )
      {
         result = false;
         error = e.what( );
         MSG_ERR( "error: %s", error.c_str( ) );
      }

      return result;
   }



   bool run( )
   {
      const char* const file = "/mnt/dev/EPAM/android/source/android-12.1.0_r8/device/epam/aosp-vhal/vehicle/hal/impl/production/config/viss/vehicle_viss_prop_mapping.json";
      std::ifstream ifstream( file );

      if( !ifstream.is_open( ) )
      {
         MSG_ERR( "Couldn't open: file '%s'", file );
         return false;
      }

      std::string json( ( std::istreambuf_iterator< char >( ifstream ) ), std::istreambuf_iterator< char >( ) );

      Root root;
      std::string error;

      // parse_to_cpp( json, root, error );
      // parse( json, error );
      parse( std::string{ "{\n   \"Signal.Drivetrain.FuelSystem.Level\" : 1000,\n}" }, error );

      return true;
   }

} // namespace test_nlohmann_json
#endif



#include "carpc/tools/Performance.hpp"

#if 0
// Given number 'a'
// Find all 'x'and 'y' numbers such that 'x + y + x*y = a'
// This could be changed to 'm*n=b' where:
// - m = x + 1
// - n = y + 1
// - b = a + 1
namespace exercise_01 {

   using TYPE = std::size_t;

   const TYPE value = 500008500036;

   struct Point
   {
      TYPE x{ 0 };
      TYPE y{ 0 };
   };

   std::vector< Point > processor( const TYPE& a )
   {
      MSG_DBG( "processing value: %zu", a );

      const TYPE b = a + 1;

      std::vector< Point > result;
      result.reserve( 100 );

      TYPE m = 1;
      TYPE limit = b / m;

      carpc::tools::Performance performance( "calculate" );
      performance.start( );

      while( ++m < limit )
      {
         if( ( b % m ) == 0 )
         {
            limit = b / m;
            result.push_back( { m - 1, limit - 1 } );
         }
      }

      performance.stop( );

      if( result.empty( ) )
         printf( "no answer\n" );

      for( auto& item: result )
         printf( "x = %zu / y = %zu\n", item.x, item.y );

      return result;
   }

} // namespace exercise_01
#endif




template< typename Test, template< typename... > class Ref >
struct is_specialization : std::false_type { };

template< template< typename... > class Ref, typename... Args >
struct is_specialization< Ref< Args... >, Ref >: std::true_type { } ;



bool test( int argc, char** argv, char** envp )
{
   MSG_MARKER( "TEST" );

   // test_stream::run( );
   // test_nlohmann_json::run( );

   MSG_MARKER( "TEST" );

   return false;
}
