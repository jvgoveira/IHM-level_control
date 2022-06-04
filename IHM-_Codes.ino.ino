/*-----------------------------------------------------------------
    @Autor: João Vitor G. de Oliveira
    ©Copyright (c) 2022 João Vitor G.
-----------------------------------------------------------------*/

//INCLUSÃO DAS BIBLIOTECAS USADAS NO PROJETO:
#include <LiquidCrystal.h>
#include <EEPROM.h>

//DEFINIÇÃO DAS PORTAS AS QUAIS ESTÃO CONECTADOS OS PINOS DO LCD:
#define EN PB4 
#define RS PC3
#define DB4 PC4
#define DB5 PC5
#define DB6 PC6
#define DB7 PC7

//DEFINIÇÃO DAS SAIDAS DOS LEDS
#define LED_AZUL PD1
#define LED_VERD PD3
#define LED_VERM PD2

//DEFINIÇÃO DAS ENTRADAS
#define L_BOMBA PA1
#define L_VALV PD6
#define L_AQUEC PD5
#define AUTMAN PD4

//DEFINIÇÃO DAS VARIÁVEIS DO PROGRAMA 
int x=1;
int bomba=0;
int autman=0;
int valvula=0;
int aquecedor=0;
LiquidCrystal (lcd,EN,RS, DB4,DB5,DB6,DB7);

//INICIALIZAÇÃO DOS PARAMETROS DA IHM:
void setup() 
{ //INICIALIZANDO AS ENTRADAS
  pinMode(AUTMAN,INPUT);
  pinMode(L_BOMBA,INPUT);
  pinMode(L_VALV,INPUT);
  pinMode(L_AQUEC,INPUT);
  
  //INICIALIZANDO AS SAIDAS
  pinMode(LED_AZUL,OUTPUT);
  pinMode(LED_VERM,OUTPUT);
  pinMode(LED_VERD,OUTPUT);

  //DEFINIÇÃO DOS DISPLAY LCD 20X4
  lcd_begin(20, 4);

/*------------------------------------------------------------
                 ROTINA DE INICIALIZAÇÃO DA IHM:
-------------------------------------------------------------*/
  digitalWrite(LED_AZUL,HIGH);
  digitalWrite(LED_VERD,HIGH);
  digitalWrite(LED_VERM,HIGH);

  lcd_setCursor(0,1);
  lcd_print_s("      SENAI-DF      ");
  lcd_setCursor(0,2);
  lcd_print_s("Designed by JV Gomes");
  delay(5000);
   
  digitalWrite(LED_AZUL,LOW);
  digitalWrite(LED_VERD,LOW);
  digitalWrite(LED_VERM,LOW);

  lcd_clear();
  lcd_setCursor(0,0);
  lcd_print_s(" STATUS DO PROCESSO ");
  lcd_setCursor(0,2);
  lcd_print_s("Bomba=DES | Valv=DES");
  lcd_setCursor(0,3);
  lcd_print_s("Aquec=DES |  MANUAL ");
}
/*-----------------------------------------------------------
            EXECUÇÃO DOS PROCESSOS CONTINUOS DA IHM:
------------------------------------------------------------*/
void loop() 
{
  //LEITURA DAS PORTAS DE ENTRADA DA IHM:
  bomba = digitalRead(L_BOMBA);
  valvula = digitalRead(L_VALV);
  aquecedor = digitalRead(L_AQUEC);
  autman = digitalRead(AUTMAN);
  switch(x)
  {
    case 1 :if(bomba==1){
              lcd_setCursor(6,2);
              lcd_print_s("LIG");
            }else{
              lcd_setCursor(6,2);
              lcd_print_s("DES");
            }
            x=2;
            break;
    case 2 :if(valvula==1){
              lcd_setCursor(17,2);
              lcd_print_s("LIG");
            }else{
              lcd_setCursor(17,2);
              lcd_print_s("DES");
            }
            x=3;
            break;
    case 3 :if(aquecedor==1){
              lcd_setCursor(6,3);
              lcd_print_s("LIG");
              }else{
              lcd_setCursor(6,3);
              lcd_print_s("DES");
            }  
            x=4;
            break;
    case 4 : if(autman==1){
              digitalWrite(LED_AZUL,HIGH);
              lcd_setCursor(12,3);
              lcd_print_s("AUTOMAT");
            }
            else{
              digitalWrite(LED_AZUL,LOW);
              lcd_setCursor(12,3);
              lcd_print_s(" MANUAL");
            }
            x=1;
            break;
  }
  
  //CONDIÇÃO PARA O ACIONAMENTO DAS LUZES:
  if(( aquecedor==1 )||( valvula==1 )||( bomba==1 )||( autman==1 )){
     digitalWrite(LED_VERD,LOW);
    digitalWrite(LED_VERM,HIGH);
  }
  else{
    digitalWrite(LED_VERD,HIGH);
    digitalWrite(LED_VERM,LOW);  
  }
}
