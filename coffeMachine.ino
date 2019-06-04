#define alimentadorChocolate 2
#define alimentadorLeite 3
#define moedorCafe 4
#define pistaoCafe 5
#define valvulaChocolate_Leite 6
#define valvulaAguaQuente 7
#define valvulaCafe 8
#define valvulaPressurizacao 9
#define buzzer 18

#define pistao 10
#define cafeLongo 11
#define cafeComLeite 12
#define cappuccino 13
#define chocolate A0
#define aguaQuente 15
#define temperaturaAgua 16
#define leitorBiometrico 17
#define coffeWithMilk 100
#define coffeChocolate 101
// entradas

int hotWaterSensor = 0,
    pistonSensor = 0,
    biometrySensor = 0,
    hotWaterButton = 0,
    smallCoffeButton = 0,
    coffeWithMilkButton = 0,
    cappuccinoButton = 0,
    chocolateButton = 0,
    able = 0;

void initializing()
{
  digitalWrite(buzzer, 1);
  delay(500);
  digitalWrite(buzzer, 0);
  clearCoffe();
  // pressurização caldeira
  hotWaterFunc();
}

void hotWaterFunc()
{
  alert("hoting");
  while (!hotWaterSensor)
  {
    readSensors();
    // Aviso que esta ligando ou aquecendo caldeira
    if (biometrySensor)
    {
      alert("hoting");
    }
  }
}
// Alertas
void alert(String type)
{
  if (type == "error")
  {
    digitalWrite(buzzer, 1);
    delay(500);
    digitalWrite(buzzer, 0);
    delay(500);
    digitalWrite(buzzer, 1);
    delay(500);
    digitalWrite(buzzer, 0);
    delay(500);
  }
  else if (type == "hoting")
  {
    digitalWrite(buzzer, 1);
    delay(500);
    digitalWrite(buzzer, 0);
    delay(500);
    digitalWrite(buzzer, 1);
    delay(500);
    digitalWrite(buzzer, 0);
    delay(500);
    digitalWrite(buzzer, 1);
    delay(500);
    digitalWrite(buzzer, 0);
    delay(500);
    digitalWrite(buzzer, 1);
    delay(500);
    digitalWrite(buzzer, 0);
    delay(500);
  }
  else if ("ok")
  {
    digitalWrite(buzzer, 1);
    delay(500);
    digitalWrite(buzzer, 0);
    delay(500);
  }
}

// função que limpa o café
void clearCoffe()
{
  int countPistonCicle = 0,
      state = 0;
  // Trigger piston
  while (countPistonCicle != 2)
  {
    readSensors();
    if (pistonSensor == 1 && state == 1)
    {
      state = 0;
      countPistonCicle++;
      //
    }
    else if (pistonSensor == 0 && state == 0)
    {
      state = 1;
    }
  }
  // Stop piston
}
// Processo de saida de agua quente
void waterOut()
{
  if (able == 1)
  {
    alert("ok");
    hotWaterFunc();
    valveOut(valvulaAguaQuente, 9500);
    able = 0;
    alert("ok");
  }
  else
  {
    alert("error");
  }
}
void chocolateOut() {
  if (able == 1)
  {
    alert("ok");
    hotWaterFunc();
    valveOut(valvulaChocolate_Leite, 9500);
    able = 0;
    alert("ok");
  }
  else
  {
    alert("error");
  }
}
void coffeOut() {
  if (able == 1)
  {
    alert("ok");
    hotWaterFunc();
    valveOut(valvulaCafe, 13000);
    able = 0;
    alert("ok");
  }
  else
  {
    alert("error");
  }
}
void coffeWithMilkOut() {
  if (able == 1)
  {
    alert("ok");
    hotWaterFunc();
    valveOut(coffeWithMilk, 13000);
    able = 0;
    alert("ok");
  }
  else
  {
    alert("error");
  }
}
void cappuccinoOut() {
  if (able == 1)
  {
    alert("ok");
    hotWaterFunc();
    valveOut(coffeChocolate, 13000);
    able = 0;
    alert("ok");
  }
  else
  {
    alert("error");
  }
}
void valveOut(int valve, int timeSet)
{
  int clearCup = 500,
      milkTime = 3000,
      timeScrashBeans = 5000;
  unsigned long currentTime = millis();
  int timeToValveAndMilk = timeSet + currentTime;
  int timePressure = 1000 + timeToValveAndMilk;
  int countPistonCicle = 0;
  int state = 0;
  if (valve)
  {
    switch (valve) {
      case valvulaChocolate_Leite:

        digitalWrite(valvulaPressurizacao, 1);
        digitalWrite(valve, 1);
        digitalWrite(alimentadorLeite, 1);
        delay(milkTime);
        digitalWrite(alimentadorLeite, 0);
        digitalWrite(alimentadorChocolate, 1);
        delay(timeSet - clearCup);
        digitalWrite(alimentadorChocolate, 0);
        delay(clearCup);
        digitalWrite(valve, 0);
        delay(1000);
        digitalWrite(valvulaPressurizacao, 0);
        break;
      case valvulaAguaQuente:
        digitalWrite(valve, 1);
        digitalWrite(valvulaPressurizacao, 1);
        delay(timeSet);
        digitalWrite(valve, 0);
        delay(1000);
        digitalWrite(valvulaPressurizacao, 0);
        break;
      case valvulaCafe:

        clearCoffe();
        digitalWrite(moedorCafe, 1);
        delay(timeScrashBeans);
        digitalWrite(moedorCafe, 0);
        digitalWrite(valve, 1);
        digitalWrite(valvulaPressurizacao, 1);
        delay(timeSet);
        digitalWrite(valve, 0);
        delay(1000);
        digitalWrite(valvulaPressurizacao, 0);
        break;
      case coffeWithMilk:
        digitalWrite(valvulaChocolate_Leite, 1);
        digitalWrite(alimentadorLeite, 1);
        digitalWrite(valvulaPressurizacao, 1);
        currentTime = millis();
        timeToValveAndMilk = timeSet + currentTime;
        timePressure = 1000 + timeToValveAndMilk;
        timeScrashBeans = 5000;
        countPistonCicle = 0;
        state = 0;
        while (timePressure + 1000 < currentTime || countPistonCicle <= 4) {
          readSensors();
          currentTime = millis();
          // Trigger piston
          if (countPistonCicle != 2 && countPistonCicle < 3)
          {
            readSensors();
            if (pistonSensor == 1 && state == 1)
            {
              state = 0;
              countPistonCicle++;
              //
            }
            else if (pistonSensor == 0 && state == 0)
            {
              state = 1;
            }
          } else if (countPistonCicle == 2) {
            countPistonCicle = 3;
            timeScrashBeans = timeScrashBeans + currentTime;
          } else if (countPistonCicle == 3) {
            countPistonCicle = 4;
            digitalWrite(moedorCafe, 1);
          } else if (countPistonCicle == 4) {
            asyncOperation(moedorCafe, timeScrashBeans, currentTime);
          }
          asyncOperation(valvulaChocolate_Leite, timeToValveAndMilk, currentTime);
          asyncOperation(alimentadorLeite, timeToValveAndMilk, currentTime);
          asyncOperation(valvulaPressurizacao, timePressure, currentTime);
        }
        digitalWrite(valvulaCafe, 1);
        digitalWrite(valvulaPressurizacao, 1);
        delay(timeSet);
        digitalWrite(valvulaCafe, 0);
        delay(1000);
        digitalWrite(valvulaPressurizacao, 0);
        break;
      case coffeChocolate:
        digitalWrite(valvulaChocolate_Leite, 1);
        digitalWrite(alimentadorChocolate, 1);
        digitalWrite(valvulaPressurizacao, 1);
        currentTime = millis();
        timeToValveAndMilk = timeSet + currentTime;
        timePressure = 1000 + timeToValveAndMilk;
        timeScrashBeans = 5000;
        countPistonCicle = 0;
        state = 0;
        while (timePressure + 1000 < currentTime || countPistonCicle <= 4) {
          readSensors();
          currentTime = millis();
          // Trigger piston
          if (countPistonCicle != 2 && countPistonCicle < 3)
          {
            readSensors();
            if (pistonSensor == 1 && state == 1)
            {
              state = 0;
              countPistonCicle++;
              //
            }
            else if (pistonSensor == 0 && state == 0)
            {
              state = 1;
            }
          } else if (countPistonCicle == 2) {
            countPistonCicle = 3;
            timeScrashBeans = timeScrashBeans + currentTime;
          } else if (countPistonCicle == 3) {
            countPistonCicle = 4;
            digitalWrite(moedorCafe, 1);
          } else if (countPistonCicle == 4) {
            asyncOperation(moedorCafe, timeScrashBeans, currentTime);
          }
          asyncOperation(valvulaChocolate_Leite, timeToValveAndMilk, currentTime);
          asyncOperation(alimentadorChocolate, timeToValveAndMilk, currentTime);
          asyncOperation(valvulaPressurizacao, timePressure, currentTime);
        }
        digitalWrite(valvulaCafe, 1);
        digitalWrite(valvulaPressurizacao, 1);
        delay(timeSet);
        digitalWrite(valvulaCafe, 0);
        delay(1000);
        digitalWrite(valvulaPressurizacao, 0);
        break;
    }
  }
}
void asyncOperation(int port, int timeExe, int currentTime) {
  if (timeExe < currentTime) {
    digitalWrite(port, 0);
  }
}
void readSensors()
{
  biometrySensor = digitalRead(leitorBiometrico);
  pistonSensor = digitalRead(pistao);
  hotWaterSensor = digitalRead(temperaturaAgua);
  smallCoffeButton = digitalRead(cafeLongo);
  coffeWithMilkButton = digitalRead(cafeComLeite);
  cappuccinoButton = digitalRead(cappuccino);
  chocolateButton = digitalRead(chocolate);
  hotWaterButton = digitalRead(aguaQuente);
}

void setup()
{
  Serial.begin(9600);
  // inicialização de portas de saida
  for (int i = 2; i <= 9; i++)
  {
    pinMode(i, OUTPUT);
  }
  pinMode(buzzer, OUTPUT);
  // inicialização de portas de entradas
  for (int i = 10; i <= 13; i++)
  {
    pinMode(i, INPUT);
  }
  pinMode(chocolate, INPUT);
  pinMode(aguaQuente, INPUT);
  pinMode(temperaturaAgua, INPUT);
  pinMode(leitorBiometrico, INPUT);
  // Procedimentos de inicialização
  initializing();
}

void loop()
{
  readSensors();
  // Inserção de credito por biometria
  if (biometrySensor)
  {
    able = 1;
  }
  // Processo de saida de agua quente
  if (hotWaterButton)
  {
    waterOut();
  }
  if (chocolateButton) {
    chocolateOut();
  }
  if (smallCoffeButton) {
    coffeOut();
    coffeOut();
  }
  if (coffeWithMilkButton) {
    coffeWithMilkOut();
  }
  if (cappuccinoButton) {
    cappuccinoOut();
  }
}
