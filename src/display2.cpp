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
}

void displayBootScreen()
{

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20, (SCREEN_HEIGHT / 2));
    display.println(F("THUNDER"));
    display.display();
    delay(1000);
    display.clearDisplay();
    display.display();
    delay(500);
}

void optionHandler(String option)
{
    if (option == "SAVE")
    {
        display.clearDisplay();
        display.display();
        memorySaveMotorVariables();
    }
    else if (option == "G_THRESHOLD")
    {
        display.clearDisplay();
        display.display();
        generateThreshold();
    }
    else if (option == "V_THRESHOLD")
    {
        display.clearDisplay();
        display.display();
        delay(300);
        while (true)
        {
            displayDrawMenu("SENSOR_THRESHOLD_MENU");
            if (buttonPressed() != "NO")
            {
                break;
            }
        }
        delay(200);
    }
    else if (option == "S_R_RAW")
    {
        display.clearDisplay();
        display.display();
        delay(300);
        while (true)
        {
            display.clearDisplay();
            display.display();
            readSensors();
            displayDrawMenu("SENSOR_RAW_MENU");
            if (buttonPressed() != "NO")
            {
                break;
            }
        }
        delay(200);
    }
    else if (option == "S_R_BIN")
    {
        display.clearDisplay();
        display.display();
        delay(300);
        while (true)
        {
            display.clearDisplay();
            display.display();
            readSensors();
            generateBinary();
            displayDrawMenu("SENSOR_BINARY_MENU");
            if (buttonPressed() != "NO")
            {
                break;
            }
        }
        delay(200);
    }
}