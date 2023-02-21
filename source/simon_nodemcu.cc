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
#define TIME_SOUND_MS 1
#define TIME_ON_LED_SECUENCE_MS 700
#define TIME_WAIT_FOR_NEXT_LED_ON_MS 300
#define TIME_NEXT_LEVEL_MS 2000

// pines de los leds. Estos son los pines donde se conectara cada led
#define LED_ROJO 2 //60
#define LED_VERDE 3
#define LED_AMARILLO 4
#define LED_AZUL 5
#define FIRST_PIN_LED_NUMBER 2

/* Definimos los pines en donde se conectara la bocina */
#define buzzer 13

// pines de los botones. Estos son los pines donde se conectaran los botones
#define BOTON_ROJO 7
#define BOTON_VERDE 8
#define BOTON_AMARILLO 9
#define BOTON_AZUL 10
#define BOTON_START 11

// game over sounds.
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0


// change this to make the song slower or faster
int tempo = 300;

enum ESTADO_ACTUAL{
  INICIO_JUEGO=0,
  START,
  JUGANDO,
  FIN_JUEGO,
  SECUENCIA_CORRECTA,
  SECUENCIA_INCORRECTA
};

enum ColorSecuencia{ROJO=0,VERDE,AMARILLO,AZUL};

int estado=INICIO_JUEGO; // variable que almacena el estado del juego
int nivelJuego=1; // el juego tendra maximo de 15 secuencias 0-14
int secuencia[15]={LED_ROJO,LED_ROJO,BOTON_AMARILLO,
                   BOTON_AMARILLO,1,BOTON_AMARILLO,0,
                   LED_ROJO,2,0,1,LED_ROJO,0,1,2}; // arreglo que almacena las secuencias
String strColorSecuencia[15];   

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melodyWin[] = {
  NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,8, //1
  NOTE_G5,4, REST,4
};

int melodyOver[] = {
  NOTE_C5,-4, NOTE_G4,-4, NOTE_E4,4, //45
  NOTE_A4,-8, NOTE_B4,-8, NOTE_A4,-8, NOTE_GS4,-8, NOTE_AS4,-8, NOTE_GS4,-8,
  NOTE_G4,8, NOTE_D4,8, NOTE_E4,-2,  

};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notesWin = sizeof(melodyWin) / sizeof(melodyWin[0]) / 2;
int notesOver = sizeof(melodyOver) / sizeof(melodyOver[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

void gameOverMarioSound(){
// iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notesOver * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melodyOver[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melodyOver[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}            

void gameWinMarioSound(){
// iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notesWin * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melodyWin[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melodyWin[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}  

/*  Funciones que se utilizaran para el funcionamiento del programa */ 
// funcion que reproduce sonido. Esta funcion se llamara cada vez que se ilumine un led
void sonidoLed( int tiempo ){
  
  for(int i=0;i<tiempo;i++){
    digitalWrite(buzzer, HIGH);
    delay(TIME_SOUND_MS);
    digitalWrite(buzzer, LOW);
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
  delay(200);
  sonidoLed(100);
  if(nivel==1){
     secuencia[0]=generarColorAleatorio();
     strColorSecuencia[0]=getColorSecuencia(secuencia[0]);
  }
  for(int i=0;i<nivel;i++){
    digitalWrite(secuencia[i] + FIRST_PIN_LED_NUMBER, HIGH);
    sonidoLed(250);
    Serial.println(strColorSecuencia[i]);
    delay(TIME_ON_LED_SECUENCE_MS);
    digitalWrite(secuencia[i] + FIRST_PIN_LED_NUMBER, LOW);  
    delay(TIME_WAIT_FOR_NEXT_LED_ON_MS);  
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
   delay(50);
   
   // identifica si se presiono algun botonColor y cual especificamente
   if(   (botonRojo == 0) || (botonVerde == 0) || (botonAmarillo == 0) || (botonAzul == 0)   ){
     Serial.println("Se presiono Boton ");
     presionoBoton=true;
     //sonidoLed(200);
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
        digitalWrite(secuencia[i] + FIRST_PIN_LED_NUMBER, HIGH);
        delay(500);
        digitalWrite(secuencia[i] + FIRST_PIN_LED_NUMBER, LOW);
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
    
    case 0:{ strColor="ROJO"; return strColor; } break;    
    case 1:{ strColor="VERDE"; return strColor; } break;
    case 2:{ strColor="AMARILLO"; return strColor; } break;
    case 3:{ strColor="AZUL"; return strColor; } break;
  }

}

void blinkLeds(int time_){
   Serial.println("CASE SECUENCIA_INCORRECTA");
   digitalWrite(LED_ROJO, HIGH);
   digitalWrite(LED_VERDE, HIGH);
   digitalWrite(LED_AMARILLO, HIGH);
   digitalWrite(LED_AZUL, HIGH);
   delay(time_);
   digitalWrite(LED_ROJO, LOW);
   digitalWrite(LED_VERDE, LOW);
   digitalWrite(LED_AMARILLO, LOW);
   digitalWrite(LED_AZUL, LOW);
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
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  
  /* Pines en donde se conectaran los botones, se configuran como entradas con resistencia interna que tiene el arduino PULLUP */
  pinMode(BOTON_ROJO, INPUT_PULLUP);
  pinMode(BOTON_VERDE, INPUT_PULLUP);
  pinMode(BOTON_AMARILLO, INPUT_PULLUP);
  pinMode(BOTON_AZUL, INPUT_PULLUP);
  /* pin bocina como salida */
  pinMode(buzzer, OUTPUT);
}
//66

/* Ciclo del arduino */
void loop(){
  
  
  /* Dependiendo del estado del juego se ejecutara un case especifico */
  switch( estado ){ 
    
    case INICIO_JUEGO:{
      Serial.println("CASE INICIO_JUEGO");
      gameWinMarioSound();
      sonidoLed(100);
      blinkLeds(1000);
      delay(1000);
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
        digitalWrite(LED_ROJO, HIGH);
       digitalWrite(LED_VERDE, HIGH);
       digitalWrite(LED_AMARILLO, HIGH);
       digitalWrite(LED_AZUL, HIGH);
       delay(700);
       digitalWrite(LED_ROJO, LOW);
       digitalWrite(LED_VERDE, LOW);
       digitalWrite(LED_AMARILLO, LOW);
       digitalWrite(LED_AZUL, LOW);
       gameOverMarioSound();
      estado=FIN_JUEGO;
    }break;
    

    
    case SECUENCIA_CORRECTA:{
            Serial.println("CASE SECUENCIA_CORRECTA ");

      sonidoYOUWIN();
      estado=JUGANDO;
      delay(TIME_NEXT_LEVEL_MS);
    }break;
    
    case FIN_JUEGO:{ 
            Serial.println("CASE FIN_JUEGO  ");

      /* Encendemos los leds de forma parpadeante para indicar que el juego ha terminado */
       boolean salir=false;
       while(salir==false){
       digitalWrite(LED_ROJO, HIGH);
       digitalWrite(LED_VERDE, HIGH);
       digitalWrite(LED_AMARILLO, HIGH);
       digitalWrite(LED_AZUL, HIGH);
       sonidoLed(100);
       delay(500);
       digitalWrite(LED_ROJO, LOW);
       digitalWrite(LED_VERDE, LOW);
       digitalWrite(LED_AMARILLO, LOW);
       digitalWrite(LED_AZUL, LOW);
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