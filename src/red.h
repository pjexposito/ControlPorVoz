#pragma once
#include <pebble.h>

enum {
  KEY_CADENA_ENVIADA = 0,

  KEY_DATO_RECIBIDO = 1
};




void init_network();
void close_network();

void envia_cadena(char * cadena);
void busca_parada();