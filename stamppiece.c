int dir = 8, puls = 9, entradaposberco = 7, entradastart = 6, statusstart = 1, statusposberco = 1, entradalerpeca = 5, statuslerpeca = 1, saidacarimbo = 12, enable = 10, velocidade;
int conta_peca = 0;
int i = 1;
int flag_iniciar=0;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x3f, 16, 2);

void setup()
{
  lcd.init();
  pinMode(dir, OUTPUT);
  pinMode (puls, OUTPUT);// Configura os pinos como saída
  pinMode (entradaposberco, INPUT);
  pinMode (entradastart, INPUT);
  pinMode (entradalerpeca, INPUT);
  pinMode (saidacarimbo, OUTPUT);
  pinMode (enable, OUTPUT);
  digitalWrite (enable, 1);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Esteira para");
  lcd.setCursor(0, 1);
  lcd.print("carimbeira");
    lcd.clear();
  delay(2000);
   lcd.clear();
}


void loop()
{

  while (1)
  {
    statusposberco = digitalRead(entradaposberco);
    statusstart = digitalRead(entradastart);

    digitalWrite (enable, 1);

         
          lcd.setCursor(0, 0);
          lcd.print("Aperte START:");
          lcd.setCursor(0, 1);
          lcd.print("---durante 3 s----");
           
    if (statusstart == 1)
    {
      i++;
      if ((i%2)==0)
      {
        flag_iniciar = 1;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("INICIANDO...");
           

           
      }
      else if ((i%2)!=0)
      {
          i=1;
          flag_iniciar = 0;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("TRAVADO...");
            
          
      }
      delay(6000);
      lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Esteira em");
           lcd.setCursor(0, 1);
          lcd.print("modo automatico");
           
    }
    while (flag_iniciar == 1)
    {
     
      if (digitalRead(entradastart) == 0)
      {
        if (statusposberco == 0)
        {
          digitalWrite (enable, 0);
          do
          {
            if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}
            digitalWrite(dir, HIGH); // Defini a direção de rotação
            digitalWrite(puls, HIGH); // Envia um pulso de um passo
            if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}
            delay(2);
            if (digitalRead(entradastart) == 1) {flag_iniciar= 0;break;}
           
            digitalWrite(puls, LOW);
            delay(2);
             if (digitalRead(entradastart) == 1) {flag_iniciar= 0;break;}
            
            statusposberco = digitalRead(entradaposberco);

          } while (statusposberco == 0);

          
          do
          {

            digitalWrite(dir, HIGH); // Defini a direção de rotação

            digitalWrite(puls, HIGH); // Envia um pulso de um passo
            if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}
            
            delay(2);
            if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}
            
            digitalWrite(puls, LOW);
            if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}
            
            delay(2);
           if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}
           
            statusposberco = digitalRead(entradaposberco);
          } while (statusposberco == 1);
        }
      } else {flag_iniciar = 0;break;}
      
      if (digitalRead(entradastart) == 0 && (flag_iniciar==1))
      {
        digitalWrite(dir, HIGH); // Defini a direção de rotação
        statuslerpeca = digitalRead(entradalerpeca);
        if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}
        
        if (statuslerpeca == 1)
        {

          //carimbar
          digitalWrite (saidacarimbo, 1);
          delay (100);
          digitalWrite (saidacarimbo, 0);
          delay (100);
          digitalWrite (saidacarimbo, 1);
          delay (100);
          digitalWrite (saidacarimbo, 0);
          delay (100);
          delay(1100);
          digitalWrite (enable, 1);

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("pecas carimbadas:");
          lcd.setCursor(0, 1);
          conta_peca++;  lcd.print(conta_peca);
          //delay(500);
        }
        
        else if (statuslerpeca == 0)
        {
          //carimbar
          digitalWrite (enable, 1);
          digitalWrite (saidacarimbo, 1);
          delay (100);
          digitalWrite (saidacarimbo, 0);
          delay (100);
          digitalWrite (saidacarimbo, 1);
          delay (100);
          digitalWrite (saidacarimbo, 0);
          delay (100);
          delay(1100);
          //delay(500);
          //carimbar
          digitalWrite (saidacarimbo, 1);
          delay (100);
          digitalWrite (saidacarimbo, 0);
          delay (100);
          digitalWrite (saidacarimbo, 1);
          delay (100);
          digitalWrite (saidacarimbo, 0);
          delay (100);
          delay(1100);
          //delay(500);
        }
      } 
     if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}

      
      if (digitalRead(entradastart) == 0 && flag_iniciar==1)
      {
        if (statusposberco == 1)
        {
          digitalWrite (enable, 0);
          do
          {

            digitalWrite(dir, HIGH); // Defini a direção de rotação

            digitalWrite(puls, HIGH); // Envia um pulso de um passo
           if (digitalRead(entradastart) == 1 || flag_iniciar == 0) {flag_iniciar = 0;break;} 
           
            delay(2);
           if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}
           
            digitalWrite(puls, LOW);
           if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}
           
            delay(2);
           if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}
           
            statusposberco = digitalRead(entradaposberco);

          } while (statusposberco == 1);

          digitalWrite(dir, HIGH); // Defini a direção de rotação
          digitalWrite(puls, HIGH); // Envia um pulso de um passo
          if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}
          
          delay(2);
         if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}
         
          digitalWrite(puls, LOW);
         if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}
          
          delay(2);
          if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}
          
          digitalWrite(puls, HIGH); // Envia um pulso de um passo
          if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}
          
          delay(2);
        if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}
        
          digitalWrite(puls, LOW);
         if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}
         
          delay(2);
         if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}
         
          digitalWrite(puls, HIGH); // Envia um pulso de um passo
         if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}
         
          delay(2);
         if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}
         
          digitalWrite(puls, LOW);
          if (digitalRead(entradastart) == 1) {flag_iniciar = 0;break;}
          
          delay(10);

        }

      } else {
        flag_iniciar = 0;
        break;
      }

    }
  }
}