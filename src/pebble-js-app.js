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

Pebble.addEventListener("appmessage",
  function(e) {
  console.log("Funcion para procesar datos");

  var mensaje = e.payload.KEY_CADENA_ENVIADA;
  var mensaje_separado = mensaje.split(" ");
    console.log("Mensaje total: "+ mensaje + ". Separado es 1: "+ mensaje_separado[0]+" 2:"+mensaje_separado[1]+" 3:"+mensaje_separado[3]+", etc.");

	//ObtenDatos();
    var dict = {"1" : 1};

    	Pebble.sendAppMessage(dict);


  }
);