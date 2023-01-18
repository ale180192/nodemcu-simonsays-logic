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
