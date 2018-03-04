#ifndef MSC_CORE_MESSAGE_H__
#define MSC_CORE_MESSAGE_H__

// required to uint8_t, String, ... ( added automatically by Arduino IDE )
#include <Arduino.h>

#define MSG_MAX_BUFFER 56
#define MSG_HEADER_INFO_MAX_BUFF 8
#define MSG_BODY_DHT22_TEMP_MAX_BUFF 6
#define MSG_BODY_DHT22_HUM_MAX_BUFF 4

namespace msc
{

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
      String info;

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
            ;
        }
        
      };


      //uint8_t msg_buffer[RH_ASK_MAX_MESSAGE_LEN];
      //uint8_t msg_buffer_length = sizeof(msg_buffer);


      msg_header header;
      body_union body;


      message();
      
      String serialize();

      void deserialize( uint8_t * buff, uint8_t size );
 
    };

} // end namespace


#endif

