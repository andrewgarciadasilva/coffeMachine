#define alimentadorChocolate 2
#define alimentadorLeite 3
#define moedorCafe 4
#define pistaoCafe 5
#define valvulaChocolate 6
#define valvulaAguaQuente 7
#define valvulaCafe 8
#define valvulaPressurizacao 9
#define buzzer "A4"

#define pistao 10
#define cafeLongo 11
#define cafeComLeite 12
#define cappuccino 13
#define chocolate "A0"
#define aguaQuente "A1"
#define temperaturaAgua "A2"
#define leitorBiometrico "A3"

// entradas

int hotWaterSensor = 0,
    pistonSensor = 0,
    biometrySensor = 0,
    hotWaterButton = 0,
    longCoffeButton = 0,
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
    valveOut(valvulaAguaQuente, 9350);
    able = 0;
    alert("ok");
  }
  else
  {
    alert("error");
  }
}

void valveOut(int valve, int time)
{
  if (valve)
  {
    digitalWrite(valve, 1);
    digitalWrite(valvulaPressurizacao, 1);
    delay(time);
    digitalWrite(valve, 0);
    delay(1000);
    digitalWrite(valvulaPressurizacao, 0);
  }
}
void readSensors()
{
  biometrySensor = digitalRead(leitorBiometrico);
  pistonSensor = digitalRead(pistao);
  hotWaterSensor = digitalRead(temperaturaAgua);
  longCoffeButton = digitalRead(cafeLongo);
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
}
