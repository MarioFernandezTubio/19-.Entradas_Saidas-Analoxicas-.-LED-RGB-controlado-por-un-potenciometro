/* 
Realiza en TinkerCAD unha simulación con Arduíno, 
que inclúa un potenciómetro e un LED RGB 
coas súas correspondentes proteccións. 
O potenciómetro permite mapear os seus valores de entrada 
a só seis, de maneira que estes valores á súa mapean 
con seis niveis de cor entre os valores 38000 e 1250000. 
Conseguintemente, ao accionar o potenciómetro, 
no LED RGB aparece unha das seis cores posible.

O programa debe sacar polo monitor serie os valores 
das seis cores en decimal, hexadecimal e binario.

Asegúrate que o programa funciona tanto para LEDs RGB 
de ánodo común, como para os de cátodo común.*/



#define pot A0
#define ledR 11
#define ledG 10
#define ledB 9


/* Selección de tipo de LED: 
true = ánodo común, 
false = cátodo común*/

bool ANODO_COMUN = false; 

void setup()
{
  pinMode(ledR,OUTPUT);
  pinMode(ledG,OUTPUT);
  pinMode(ledB,OUTPUT);
  
  Serial.begin(9600);      // Para ver o Monitor Serie
}

void loop()
{
// Lemos o potenciómetro 0-1023 bits
  int Potvalor = analogRead(pot); 
  
// Rango de valores numéricos da cor que nos pide o exercicio.
  const long minimoCOR = 38000;
  const long maximoCOR = 1250000;
  
/* Para unha lectura estable escollemos un rango de 50 --- 975 bits
   Traducido serían entre 0,25V --- 4,75V.
  
   Limitamos o rango de entrada para asegurarnos de que 
   map() só recibe valores no rango esperado.

             constrain(valor,   min, max)*/
  Potvalor = constrain(Potvalor, 50, 975);
  
/* Remapear o rango para que "50 sexa 0" e "975 sexa 1023".
            "map(valor, fromLow, fromHigh, toLow, toHigh)"*/
  Potvalor = map(Potvalor, 50,    975,       0,     1023);
  
  
// Mapear os valores dentro das 6 cores dispoñibles.
  int Cores = map(Potvalor, 0, 1023, 0, 5);

// Calculamos os 6 tipos de cores en decimal.
// Dividimos /5 para separar en 6 valores.
// 38000   280400   522800   765200   1007600   1250000

/* Exemplo do punto de partida que sería 38000:
  long valor = 38000 + ((1250000 - 38000) / 5) * 0; 
*/ 
  
  long valor = minimoCOR + ((maximoCOR - minimoCOR) / 5) * Cores;
 
  
/******* TRADUCIMOS "long valor" A VALORES RGB *******/

  // Extraemos os compoñentes de cada cor (Vermello, Verde, Azul)
 
  // Os primeiros (2 díxitos hexadecimal) 8 bits para o vermello.
  int vermello = (valor >> 16) & 0xFF;
  
  // Os seguientes (2 díxitos hexadecimal)8 bits para o verde.
  int verde = (valor >> 8) & 0xFF; 
  
  // Os últimos (2 díxitos hexadecimal)8 bits para o azul. 
  int azul = valor & 0xFF;              



/******* DECIDIMOS SE TEMOS ÁNODO OU CÁTODO COMÚN *******/
  
// Como as cores teñen 256 bits o rango é 0-255.
  
  // Se o ÁNODO_COMÚN é TRUE...

  #ifdef ANODO_COMUN			
  vermello = 255 - vermello;
  verde = 255 - verde;
  azul = 255 - azul;
  
  // Se o ÁNODO_COMÚN é FALSE...
  
  #endif
  analogWrite(ledR, vermello);
  analogWrite(ledG, verde);
  analogWrite(ledB, azul);
  
  
/***************  Monitor Serie  ***************/
  
// Imprimimos os nomes na primeira liña
	Serial.println("DECIMAL             HEXADECIMAL                  BINARIO  ");

// Imprimimos os valores na segunda liña
	Serial.print(valor);
	Serial.print("               ");
	Serial.print(valor, HEX);
	Serial.print("                   ");
	Serial.println(valor, BIN);
  
// Separamos entre impresións
Serial.println("");
   
}
