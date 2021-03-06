#include <pebble.h>
#include "red.h"

static Window *s_main_window;
static TextLayer *s_output_layer;

static DictationSession *s_dictation_session;
static char s_last_text[512];


/******************************* Dictation API ********************************/

static void dictation_session_callback(DictationSession *session, DictationSessionStatus status, 
                                       char *transcription, void *context) {

  if(status == DictationSessionStatusSuccess) {
    // Display the dictated text
    bool correcto = strstr(transcription, "Apaga la luz");
    if (correcto)
      snprintf(s_last_text, sizeof(s_last_text), "Ole. Ahora se apagan las luces");
    else
      snprintf(s_last_text, sizeof(s_last_text), "Transcription:\n\n%s", transcription);
    text_layer_set_text(s_output_layer, s_last_text);
      APP_LOG(APP_LOG_LEVEL_DEBUG, "Ahora se envía cadena");


    envia_cadena(transcription);
  } else {
    // Display the reason for any error
    static char s_failed_buff[128];
    snprintf(s_failed_buff, sizeof(s_failed_buff), "Transcription failed.\n\nError ID:\n%d", (int)status);
    
    text_layer_set_text(s_output_layer, s_failed_buff);
  }
}

/************************************ App *************************************/

static void inicia_dictado(){
    dictation_session_start(s_dictation_session);


}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  // Start voice dictation UI
  dictation_session_start(s_dictation_session);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

static void window_load(Window *window) {
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Windows Load");



  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_output_layer = text_layer_create(GRect(bounds.origin.x, (bounds.size.h - 24) / 2, bounds.size.w, bounds.size.h));
  text_layer_set_text(s_output_layer, "Iniciando...");
  text_layer_set_text_alignment(s_output_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_output_layer));
  // Inicia el dictado
  app_timer_register(10, inicia_dictado, 0);



}

static void window_unload(Window *window) {
  text_layer_destroy(s_output_layer);

}

static void init() {
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Init");


  s_main_window = window_create();
  // Descomentar para habilitar el click
  window_set_click_config_provider(s_main_window, click_config_provider);
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(s_main_window, true);

  // Create new dictation session
  s_dictation_session = dictation_session_create(sizeof(s_last_text), dictation_session_callback, NULL);
  dictation_session_enable_confirmation(s_dictation_session, false);
  
  init_network();

}

static void deinit() {
  // Free the last session data
  dictation_session_destroy(s_dictation_session);
  close_network();
  window_destroy(s_main_window);
}

int main() {
  init();
  app_event_loop();
  deinit();
}
