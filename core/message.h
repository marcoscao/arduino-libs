#ifndef MSC_CORE_MESSAGE_H__
#define MSC_CORE_MESSAGE_H__

#include <Arduino.h>


#define MSG_MAX_BUFFER 32

#define MSG_HEADER_INFO_MAX_BUFF 8
#define MSG_BODY_DHT22_TEMP_MAX_BUFF 6
#define MSG_BODY_DHT22_HUM_MAX_BUFF 4


namespace msc
{
  
    struct message;
    struct msg_header;
    struct msg_body_pir;
    struct msg_body_dht22;


    enum message_type
    {
        MT_UNKNOW = 0,
        MT_PIR,
        MT_DHT22
    };


    void set_message_value( String const & s, char & field, int sz_max );


    struct msg_header
    {
      message_type type;
      uint8_t body_size;
      char info[ MSG_HEADER_INFO_MAX_BUFF ];

      void set_info( String const & s );

      String serialize();
    };


    struct msg_body 
    {
    
        virtual String serialize() = 0;
    
    };


    struct msg_body_pir : public msg_body
    {
      bool presence;

      String serialize();

    };


    struct msg_body_dht22 : public msg_body
    {
      // "25.78"
      float temperature;

      // "100"
      float humidity;

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

      String serialize();

      void deserialize( String const & s);

    };


    struct message
    {
      union body_union
      {
        msg_body_pir body_pir;
        msg_body_dht22 body_dht22;

        body_union()
        {
          
        }
        
      };

      msg_header header;
      body_union body;

      message();
      static void set_value( String const & s, char & field, int sz_max );
      String serialize();
    };



} // end namespace


#endif



