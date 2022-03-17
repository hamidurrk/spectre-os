#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "display.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// On an arduino MEGA 2560: 20(SDA), 21(SCL)
#define OLED_RESET 10       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_SSD1306 display(OLED_RESET);

// External Functions in use
extern String buttonPressed();
//--------- External important functions---------------------------------------------------------
extern void memorySaveMotorVariables();
extern void generateThreshold();
extern void readSensors();
extern void generateBinary();
extern void Run();
//--------- External important variables----------------------------------------------------------
extern float motorVariables[4];
extern float &motorSpeed;
extern float &P;
extern float &I;
extern float &D;
const int numOfSensors = 8;
extern int sensorThreshold[numOfSensors];
extern int sensorRawReading[numOfSensors];
extern boolean sensorBinaryReading[numOfSensors];

// Global variables related to Option Selector
int optX = 2;
int optY = 2;
int optH = 7;
const char *mainMenuOptions[6] = {
    "PID_MENU",
    "SENSOR_MENU",
    "SERVO_MENU",
    "SONAR_MENU",
    "MEMORY_MENU",
    "RUN"};
const char *PIDoptions[6] =
    {
        "M_SP",
        "P",
        "I",
        "D",
        "SAVE",
        "BACK"};
const char *sensorMenuOptions[6] = {
    "G_THRESHOLD",
    "V_THRESHOLD",
    "S_R_BIN",
    "S_R_RAW",
    "",
    "BACK"};

void displaySetup()
{
    Wire.begin();
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextColor(WHITE);
    // display.setTextSize(1);
}