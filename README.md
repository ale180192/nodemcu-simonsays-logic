# nodemcu-simonsays-logic


### Cargar programa a la tarjeta NodeMCU v3(Lolin)

1.- Instalar la ultima version de Arduino
2.- Instalar el plugin que nos permite programar nuestra tarjeta Nodemcu desde arduino
3.- En mac me parece se necesita instalar los drivers ch340G del usb
4.- Abrir nuestra aplicacion Arduino y configurar los siguientes parametros:
 * menu Tools -> board "NodeMCU 1.0 (ESP-12E Module)"-> Esp8266 Boards (3.0.2) -> NodeMCU 1.0 (ESP-12E Module)
 * menu Tools -> Port: "dev/cu.usbserial-14210" ==> Este es el nombre del puerto al que se conecto mi tarjeta en mi computadora.
5.- Con esto podemos cargar el programa "blink" que viene de ejemplo o cargar nuestro propio programa:
 * Ejemplo blink: File -> Examples -> ESP8266 -> Blink



 ### Documentacion:
  * [ESP8266EX MCU datasheet](https://www.espressif.com/sites/default/files/documentation/0a-esp8266ex_datasheet_en.pdf)


  ### Ejemplo del juego Simon
   * [Simon online](https://freesimon.org/)




### Caracteristicas del juego:
 * El juego deberia tener al menos 3 niveles de dificultad:
    * facil: Tener un maximo score de 5 secuencias
    * normal: Tener un maximo score de 10 secuencias
    * legendario: Tener un maximo score de 25 secuencias

* El juego debera tener sonido
* El juego debera tener 4 colores diferentes
* Cuando el jugador supere el nivel configurado se debera abrir el cerrojo electromecanico.
* Cuando el jugador supere el juego los leds deberan encender en una secuencia especifica.

### Material
 * Tarjeta arduino nano
 * push buttons con LED's color verde, rojo, amarillo y azul integrados
 * madera para colocar los leds
 * push button normalmente abierto color rojo
 * buzzer pasivo
 * protoboard
 * placa fenolica, soldadura, pasta para soldar, cautin, alambre calibre 22

 #### push buttons y leds
 * cable verde es positivo para led(pin 1), amarillo es negativo para led(pin 2) 
 * negro es comun, azul normalmente abierto y rojo normalmente cerrado
