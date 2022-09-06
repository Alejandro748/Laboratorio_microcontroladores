//Laboratorio de microcontroladores
//Laboratorio 1: Bingo
//Alejandro Chacón Vargas B61871

#include <stdlib.h>
#include <pic14/pic12f675.h>
#include <stdio.h>
#define BOTON GPIO3//es justamente el boton que esta conectado de GPIO3
#define numero 16 //numero maximo de numeros que se muestran en el display
#define mask 0x03 // mascara que se utiliza para el algoritmo lsfr
#define CONTROLADOR GPIO4 //controla cual display es el que se enciende

void LED_display_switching(unsigned char display, unsigned char display2); 
unsigned char lfsr(unsigned char seed); //se utiliza algortimo lfsr para la generacion aleatoria de salidas
void delay (unsigned int tiempo); //esto se agarra del holapic, para el delay entre numeros.
void setup(); 
unsigned char mascara(unsigned char num); //esto para la mascara xor
void main(void) 
{ 
 setup(); 
 const unsigned int time = 100; //con 100 sera suficiente?
 unsigned char c = 0; //se inicializa el contador
 unsigned char seed = 7;  
 unsigned char display; 
 unsigned char display2; 
     while(1){ 
      while(c<numero){ 
       if(!BOTON){ // esto sucede si se presiona el botón boton
    seed = lfsr(seed); 
    display = seed; 
    display2 = seed - c; 
    display2 = lfsr(display2); 
    LED_display_switching(display, c); 
    c++; // por alguna razon este contador se resetea en 1 
   } 
  }  
 } 
} 

void setup(){ //aca se inicializan los pines
 typedef unsigned int word; 
 word __at 0x207 __CONFIG = (_WDTE_OFF & _WDT_OFF & _MCLRE_OFF); 
     TRISIO = 0b00000000; //Poner todos los pines como salidas
    GPIO = 0x00; //Poner pines en bajo
    ANSEL = 0x00;  
} 
 
 
 //se utiliza el algortimo lsfr para generar un numero aleatorio
unsigned char lfsr(unsigned char seed) { 
 unsigned char out_bit; 
 out_bit = seed & mask; 
 out_bit = out_bit >>1 ^ out_bit; 
 out_bit &= 0x01; 
 seed>>=1; 
 seed|=(out_bit<<3); 
 seed &= 0x0F; // No se puede pasar de 15, por eso se limpia acá  
  
 if(seed >= 10){ 
  seed = (seed>>1) - 1; 
  return seed; 
 } 
 else{ 
  return seed; 
 } 
} 
 
 
void delay(unsigned int tiempo) 
{ 
 unsigned int i; 
 unsigned int j; 
 for(i=0;i<tiempo;(i)++) 
 for(j = 0; j<1275; (j)++); 
}

void main(void){ //aqui se inicializan los registros
    TRISIO = 0x00; //se ponen todos los pines como salidas
    GPIO = 0x00; //se ponen todos los pines en bajo
}