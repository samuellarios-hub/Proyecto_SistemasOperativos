#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

// Pines
#define SENSOR_PIN 34
#define SD_CS 5

int sensorValue = 0;

// Leer sensor
void TaskReadSensor(void *pvParameters) {
  while (true) {
    sensorValue = analogRead(SENSOR_PIN);
    Serial.print("Sensor: ");
    Serial.println(sensorValue);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

// Escribir en SD
void TaskWriteSD(void *pvParameters) {
  while (true) {
    File file = SD.open("/datos.txt", FILE_WRITE);

    if (file) {
      file.print("Valor: ");
      file.println(sensorValue);
      file.close();
      Serial.println("Guardado en SD");
    } else {
      Serial.println("Error SD");
    }

    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);

  // Inicializar SPI correctamente
  SPI.begin(18, 19, 23, SD_CS); // SCK, MISO, MOSI, CS

  // Inicializar SD
  if (!SD.begin(SD_CS)) {
    Serial.println("Error inicializando SD");
    return;
  }

  Serial.println("SD inicializada correctamente");
  File file = SD.open("/datos.txt", FILE_WRITE);
if (file) {
  file.println("Inicio de archivo");
  file.close();
  Serial.println("Archivo creado correctamente");
} else {
  Serial.println("Error creando archivo");
}

  // Crear tareas
  xTaskCreate(TaskReadSensor, "Sensor", 2048, NULL, 1, NULL);
  xTaskCreate(TaskWriteSD, "SD", 4096, NULL, 1, NULL);
}

void loop() {
  
}