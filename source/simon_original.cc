/*
Programa Simon Dice, juego que encinde leds de distintos colores aleatoriamente en forma de secuencias
que van incrementando el nivel de dificultad. El juego consiste en ir repitiendo las secuencias de los leds
presionando botone s
*/


// Funcion que reproduce sonido. Esta funcion se llamara cada vez que ocurre GAME OVER en el juego
void sonidoGAMEOVER(){
  
}
//20
// funcion que reproduce sonido. Esta funcion se llamara cada vez que la secuencia de colores se repitio correctamente
void sonidoYOUWIN(){  
}





   //50


// pines de los leds. Estos son los pines donde se conectara cada led
#define melodyPin 43
#define LED_ROJO 22 //60
#define LED_VERDE 23
#define LED_AMARILLO 24
#define LED_AZUL 25

/* Definimos los pines en donde se conectara la bocina */
#define BOCINA 43

// pines de los botones. Estos son los pines donde se conectaran los botones
#define BOTON_ROJO 38
#define BOTON_VERDE 39
#define BOTON_AMARILLO 40
#define BOTON_AZUL 41
#define BOTON_START 42

// otras variables

enum ESTADO_ACTUAL{
  INICIO_JUEGO=0,
  START,
  JUGANDO,
  FIN_JUEGO,
  SECUENCIA_CORRECTA,
  SECUENCIA_INCORRECTA
};

enum ColorSecuencia{ROJO=0,VERDE,AMARILLO,AZUL};

int estado=FIN_JUEGO; // variable que almacena el estado del juego
int nivelJuego=1; // el juego tendra maximo de 15 secuencias 0-14
int secuencia[15]={LED_ROJO,LED_ROJO,BOTON_AMARILLO,
                   BOTON_AMARILLO,1,BOTON_AMARILLO,0,
                   LED_ROJO,2,0,1,LED_ROJO,0,1,2}; // arreglo que almacena las secuencias
String strColorSecuencia[15];                


/*  Funciones que se utilizaran para el funcionamiento del programa */ 
// funcion que reproduce sonido. Esta funcion se llamara cada vez que se ilumine un led
void sonidoLed( int tiempo ){
  
  for(int i=0;i<tiempo;i++){
    digitalWrite(BOCINA,HIGH);
    delay(1);
    digitalWrite(BOCINA,LOW);
    delay(1);
  }
}





// funcion que genera el numero aleatorio del intervalo 0 a 3 para seleccionar el siguiente color de la secuencia
int generarColorAleatorio(){
  randomSeed(analogRead(A0));
  return random(4);
}




// Funcion que manda al siguiente nivel del juego, solo se le pasa como parametro el arreglo que contiene las secuencias anteriores y el nivel del juego
void siguienteNivel(int secuencia[],int &nivel){
  Serial.println(" Entrando en funcion siguienteNivel ");
  if(nivel==1){
     secuencia[0]=generarColorAleatorio();
     strColorSecuencia[0]=getColorSecuencia(secuencia[0]);
  }
  for(int i=0;i<nivel;i++){
    digitalWrite(secuencia[i]+22,HIGH);
    sonidoLed(250);
    Serial.println(strColorSecuencia[i]);
    delay(1000);
    digitalWrite(secuencia[i]+22,LOW);  
    delay(500);  
  } // fin for
  int numeroGenerado=generarColorAleatorio();
  Serial.println(numeroGenerado);
secuencia[nivel]=numeroGenerado;
strColorSecuencia[nivel]=getColorSecuencia(  secuencia[nivel]  );
nivel++;
delay(200);

} // fin funcion siguienteNivel


// Funcion que lee la secuencia de los botones presionados, retorna true si la secuencia es correcta y false para una secuencia incorrecta
boolean lecturaBotonesPresionados(int &nivelJuego){
  Serial.println(" Entrando en funcion lecturaBotonesPresionados ");
  String strBotonPresionado;
  //40
  
  for(int i=0;i<=nivelJuego;){
   int botonPresionado=-1; 
   boolean presionoBoton=false;
   int botonRojo=digitalRead( BOTON_ROJO );//38
   int botonVerde=digitalRead( BOTON_VERDE);
   int botonAmarillo=digitalRead( BOTON_AMARILLO );
   int botonAzul=digitalRead( BOTON_AZUL );
   delay(100);
   
   // identifica si se presiono algun botonColor y cual especificamente
   if(   (botonRojo == 0) || (botonVerde == 0) || (botonAmarillo == 0) || (botonAzul == 0)   ){
     Serial.println("Se presiono Boton ");
     presionoBoton=true;
     sonidoLed(200);
     //int botonPresionado=20;//91
     if(botonRojo==0){ botonPresionado=0; strBotonPresionado="botonRojo"; }else
     if(botonVerde==0){ botonPresionado=1; strBotonPresionado="botonVerde"; }else
     if(botonAmarillo==0){ botonPresionado=2; strBotonPresionado="botonAmarillo"; }else
     if(botonAzul==0){ botonPresionado=3; strBotonPresionado="botonAzul"; }
        //150   
   }
   
   if(presionoBoton==true){
     if(secuencia[i]==botonPresionado){
        Serial.println(strBotonPresionado);
        digitalWrite(secuencia[i]+22,HIGH);
        delay(500);
        digitalWrite(secuencia[i]+22,LOW);
        i++; } else{
          Serial.println("Secuencia Incorrecta: "+strBotonPresionado);
          return false;
        i=(nivelJuego)++;
        }
     
     // Verifica que toda halla terminado toda la secuencia y devuelve true
   if(i==(nivelJuego-1)){return true;}   
   }

} // fin de for

} // fin funcion lecturaBotonesPresionados


/* funcion que identifica el color del boton presionado y regresa el nombre del color
   se le pasa como argumento un int de 0 a 3 donde cada int le corresponde un color
   0=ROJO ; 1=VERDE ; 2=AMARILLO ; 3=AZUL */
   
String getColorSecuencia(int numeroColor){
  
  String strColor;
  
  switch(numeroColor){
    
    case 0:{
      strColor="ROJO";
      //return strColor;
      }break;
    
    case 1:{ strColor="VERDE"; return strColor; } break;
    
    case 2:{ strColor="AMARILLO"; return strColor; } break;
    
    case 3:{ strColor="AZUL"; return strColor; } break;
  }

}

/******************************************************************************************
*******************************************************************************************
*******************************************************************************************
/******************************************************************************************
*******************************************************************************************
*******************************************************************************************
/******************************************************************************************
*******************************************************************************************
*******************************************************************************************



//50000000000
/* Configuracion del arduino */
void setup(){
  
  /* Pines en donde se conectaran los led, se configuran como salidas */
  Serial.begin(9600);
  pinMode(LED_ROJO,OUTPUT);
  pinMode(LED_VERDE,OUTPUT);
  pinMode(LED_AMARILLO,OUTPUT);
  pinMode(LED_AZUL,OUTPUT);
  /* Pines en donde se conectaran los botones, se configuran como entradas con resistencia interna que tiene el arduino PULLUP */
  pinMode(BOTON_ROJO,INPUT_PULLUP);
  pinMode(BOTON_VERDE,INPUT_PULLUP);
  pinMode(BOTON_AMARILLO,INPUT_PULLUP);
  pinMode(BOTON_AZUL,INPUT_PULLUP);
  /* pin bocina como salida */
  pinMode(BOCINA,OUTPUT);
}
//66

/* Ciclo del arduino */
void loop(){
  
  
  /* Dependiendo del estado del juego se ejecutara un case especifico */
  switch( estado ){ 
    
    case INICIO_JUEGO:{
      Serial.println("CASE INICIO_JUEGO");
      nivelJuego=1;
      estado=JUGANDO;
      
      
   
    }break;
    //81
    
    case JUGANDO:{
      Serial.println("CASE JUGANDO ");
      siguienteNivel(secuencia,nivelJuego);
      delay(100);
      estado=lecturaBotonesPresionados(nivelJuego)?SECUENCIA_CORRECTA:SECUENCIA_INCORRECTA;
    }break;
   
    
    case SECUENCIA_INCORRECTA:{
      Serial.println("CASE SECUENCIA_INCORRECTA");
      sonidoGAMEOVER();
      estado=FIN_JUEGO;
    }break;
    

    
    case SECUENCIA_CORRECTA:{
            Serial.println("CASE SECUENCIA_CORRECTA ");

      sonidoYOUWIN();
      estado=JUGANDO;
    }break;
    
        case FIN_JUEGO:{ 
            Serial.println("CASE FIN_JUEGO  ");

      /* Encendemos los leds de forma parpadeante para indicar que el juego ha terminado */
         boolean salir=false;
         while(salir==false){
        
       digitalWrite(LED_ROJO,HIGH);
       digitalWrite(LED_VERDE,HIGH);
       digitalWrite(LED_AMARILLO,HIGH);
       digitalWrite(LED_AZUL,HIGH);
       sonidoLed(300);
       delay(500);
       digitalWrite(LED_ROJO,LOW);
       digitalWrite(LED_VERDE,LOW);
       digitalWrite(LED_AMARILLO,LOW);
       digitalWrite(LED_AZUL,LOW);
       delay(500);
       
       if( digitalRead(BOTON_START)==LOW ){
         delay(5);
         if( digitalRead(BOTON_START)==LOW ){
           delay(5);
           if(digitalRead(BOTON_START)==LOW )
           {
              estado=INICIO_JUEGO;
              salir=true ;
            } 
         }
       } // fin de if esterno
       
      } // fin while

      
    }break;
    
    default: { /* No hace nada */
      
    }break;

  }
  
  
}