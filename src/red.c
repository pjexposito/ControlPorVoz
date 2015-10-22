#include <pebble.h>
#include "red.h"


static void appmsg_in_received(DictionaryIterator *received, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Datos recibidos.");

  (void) context;	
  Tuple *t_tipo = dict_find(received, KEY_DATO_RECIBIDO);

  if (t_tipo->value->uint32 == 1)
    {  
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Todo OK");


  }
  else
  {  
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Fallo");


  }
}

static void appmsg_in_dropped(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "In dropped: %i", reason);
  // Request a new update...
  //request_weather();
}

static void appmsg_out_sent(DictionaryIterator *sent, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Out sent.");
}


void init_network()
{
  app_message_register_inbox_received(appmsg_in_received);
  app_message_register_inbox_dropped(appmsg_in_dropped);
  app_message_register_outbox_sent(appmsg_out_sent);
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());		



}

void close_network()
{
  app_message_deregister_callbacks();
}

void envia_cadena(char * cadena)
{
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

  dict_write_cstring(iter, KEY_CADENA_ENVIADA, cadena);

  app_message_outbox_send();
}



