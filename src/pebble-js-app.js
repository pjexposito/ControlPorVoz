var sitios = {uno: 1, dos: 2, tres: 3, };

function HTTPGET(url) {
	var req = new XMLHttpRequest();
	req.open("GET", url, false);
	req.send(null);
	return req.responseText;
}

var ObtenDatos = function() {
  var response = HTTPGET("https://dl.dropboxusercontent.com/u/119376/data.dat");
  //console.log(response);

	var json = JSON.parse(response);
	var data0 = json.main.data0;

  var dict = {"0" : data0};
	
	Pebble.sendAppMessage(dict);
};

Pebble.addEventListener("ready",
  function(e) {
	//App is ready to receive JS messages
  console.log("Aplicacion lista");
  }
);

function procesa_mensaje(mensaje)
{
  var encender = -1; // Encender no tiene valor asignado
  var mensaje_separado = mensaje.split(" ");
  console.log("Mensaje total: "+ mensaje + ". Separado es 1: "+ mensaje_separado[0]+" 2:"+mensaje_separado[1]+" 3:"+mensaje_separado[2]+", etc.");
  
  // El formato es opciones es {Palabra_hablada: PIN_EN_ARDUINO}
  var opciones = {"luz" : '0', "lámpara" : '1', "led": '2'};
  
  var w_encender = ["conecta", "enciende", "enchufa", "activa", "prende", "conectar","encender", "activar", "prender", "enchufar"];
  var w_apagar = ["desconecta", "apaga", "desenchufa", "desactiva", "para", "apagar", "desconectar", "desenchufar", "desactivar", "parar"];

  if (w_encender.indexOf(mensaje_separado[0]) > -1)
    {
        encender = true;
    }
  if (w_apagar.indexOf(mensaje_separado[0]) > -1)
    {
        encender = false;
    }
  console.log("El valor de encender es: "+encender+" para "+  opciones[mensaje_separado[2]]);
}

Pebble.addEventListener("appmessage",
  function(e) {
  console.log("Funcion para procesar datos");
  console.log(sitios.uno);
  var mensaje = e.payload.KEY_CADENA_ENVIADA;
  procesa_mensaje(mensaje.toLowerCase());
	//ObtenDatos();

    	Pebble.sendAppMessage(dict);


  }
);