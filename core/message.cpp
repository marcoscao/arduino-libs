#include "message.h"

namespace msc
{

void set_message_value( String const & s, char * field, int sz_max )
{
    int tot = s.length() + 1;
    if ( s.length() > sz_max )
      tot = sz_max;

    s.toCharArray( field, tot );
}

message::message()
{
  
}

String message::serialize()
{
  String s_body;

  switch ( header.type )
  {
    case MT_PIR : s_body = body.body_pir.serialize(); break;
    case MT_DHT22 : s_body = body.body_dht22.serialize(); break;
    default :
      Serial.println( "*********** Message Send warning: header with no body type defined" );
      //return String();
  }

  header.body_size = s_body.length();

  String s = header.serialize();

  s += '~' + s_body;

  //char buff[ MSG_MAX_BUFFER ];
  //set_message_value( s, buff, MSG_MAX_BUFFER );

  return s;
}

void message::deserialize( uint8_t * buff, uint8_t size )
{
    message_type type;
    uint8_t body_size;

    String str="";

    int i = 0;
    for ( ; ( i < size ) && ( (char)buff[i] != '#' ); ++i )
    {    
        str +=(char)buff[i];
    }

    //Serial.println("--- Deserialize. Reading type: ");
    //Serial.println( str );

    header.type = str.toInt();   

    ++i;
    str.remove(0);
    for ( ; ( i < size ) && ( (char)buff[i] != '#' ); ++i )
        str +=(char)buff[i];

    //Serial.println("--- Deserialize. Reading body_size: ");
    //Serial.println( str );

    header.body_size = str.toInt();   

    ++i;
    str.remove(0);
    for ( ; ( i < size ) && ( (char)buff[i] != '~' ); ++i )
        str +=(char)buff[i];

    //Serial.println("--- Deserialize. Reading header info: ");
    //Serial.println( str );

    header.info = str;   


    //// locate body section ( searching for '~' split char 
    //for ( ; ( i < size ) && ( (char)buff[i] != '~' ); ++i );
    //Serial.println("--- Deserialize. body section at pos: ");
    //Serial.println( i );
    
    ++i;
    str.remove(0);
    for ( ; i < size ; ++i )
        str +=(char)buff[i];

    Serial.println();
    Serial.print( " Message length:");
    Serial.println( size );
    Serial.println( " Message data:");
    Serial.println( "  Header:");
    Serial.print(   "    - type: \'");
    Serial.print( header.type );
    Serial.println( "\'");
    Serial.print(   "    - body_size: \'");
    Serial.print( header.body_size );
    Serial.println( "\'");
    Serial.print(   "    - info: \'");
    Serial.print( header.info );
    Serial.println( "\'");
    Serial.println( "  Body:");
    Serial.println( str );
    Serial.println();
    Serial.println("--------------------------------------------------------------");
    
}

String msg_header::serialize()
{
  String s;

  //Serial.println( "serialized: Header type: " );
  int v = static_cast<int>(type);
  //Serial.println( v );
  
  s = v;
  s += '#'; 
  s += body_size;
  s += '#'; 
  s += info;

  //Serial.println( "->>>>>> Header serialized:");
  //Serial.println(s );
  return s;
}

String msg_body_pir::serialize()
{
    String s( presence );
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
    s += '#';
    s += humidity;

    return s;
}

void msg_body_dht22::deserialize( String const & s)
{

}

} // end namespace


