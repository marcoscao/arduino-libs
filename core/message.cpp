#include "message.h"


class String;

namespace msc
{

message::message()
{
  
}

  
  String msg_body_pir::serialize()
  {
    String s = "";
    return s;
  }

//  void set_temperature( String const & s )
//  {
//    int tot = s.length() + 1;
//    if ( s.length() > MSG_BODY_DHT22_TEMP_MAX_BUFF )
//      tot = MSG_BODY_DHT22_TEMP_MAX_BUFF;
//
//    s.toCharArray( temperature, tot );
//  }
//
//  void set_humidity( String const & s )
//  {
//    int tot = s.length() + 1;
//    if ( s.length() > MSG_BODY_DHT22_HUM_MAX_BUFF )
//      tot = MSG_BODY_DHT22_HUM_MAX_BUFF;
//
//    s.toCharArray( humidity, tot );
//  }

  String msg_body_dht22::serialize()
  {
    String s;
    s += temperature;
    s += humidity;

    return s;
  }

  void msg_body_dht22::deserialize( String const & s)
  {

  }


void set_message_value( String const & s, char & field, int sz_max )
{
    int tot = s.length() + 1;
    if ( s.length() > sz_max )
      tot = sz_max;

    s.toCharArray( &field, tot );
}


void msg_header::set_info( String const & s )
{
  //set_message_value( s, &info, MSG_HEADER_INFO_MAX_BUFF );

  //int tot = s.length() + 1;
  //if( s.length() > MAX_HEADER_INFO_BUFF )
  //  tot = MAX_HEADER_INFO_BUFF;

  //s.toCharArray( info, tot );
}



String msg_header::serialize()
{
  String s;

  s = type + "\0";
  s += body_size;
  //s += info + "\0";

  return s;
}



String message::serialize()
{
  String s_body;

  switch ( header.type )
  {
    case MT_DHT22 : s_body = body.body_dht22.serialize(); break;
    default :
      Serial.println( "*********** Message Send error: header type not defined" );
      return String();
  }

  //header.set_body_size( s_body.length() );
  header.body_size = s_body.length();

  String s = header.serialize();

  s += "\0" + s_body;

  char buff[ MSG_MAX_BUFFER ];

  set_message_value( s, buff[0], MSG_MAX_BUFFER );

  return s;
}


} // end namespace


