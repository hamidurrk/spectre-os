#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "display.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// On an arduino MEGA 2560: 20(SDA), 21(SCL)
#define OLED_RESET 10       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
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
    //display.setTextSize(1);
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

void displayBootScreen()
{

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20, 12);
    display.println(F("THUNDER"));
    display.display();
    delay(1000);
    display.clearDisplay();
    display.display();
    delay(500);
}

void displayMenu(String menu_type)
{
    delay(300);
    displayDrawMenu(menu_type);
    displayOptionSelector(menu_type);
}

void displayDrawMenu(String menuType)
{
    int x = 14;
    int y = 2;
    display.clearDisplay();
    // Draw Horizontal line
    for (int16_t i = 0; i < display.height(); i += 10)
    {
        display.drawLine(0, i, display.width() - 1, i, SSD1306_WHITE);
    }

    if (menuType == "MAIN_MENU")
    {
        // Drawing the gridlines
        display.drawLine(0, 0, 0, display.height() - 5, SSD1306_WHITE);
        display.drawLine(10, 0, 10, display.height() - 5, SSD1306_WHITE);
        display.drawLine(display.width() - 1, 0, display.width() - 1, display.height() - 5, SSD1306_WHITE);

        // drawing the options
        display.setTextSize(1);              // Set the text size
        display.setTextColor(SSD1306_WHITE); // Set the text color

        // Push all the options to the display buffer
        for (int optionsIterator = 0; optionsIterator < 6; optionsIterator++, y += 10)
        {
            display.setCursor(x, y);                           // Set the cursor position . The top left position is 0,0
            display.println(mainMenuOptions[optionsIterator]); // Print from the cursor position
        }
    }
    else if (menuType == "PID_MENU")
    {
        display.drawLine(0, 0, 0, display.height() - 5, SSD1306_WHITE);
        display.drawLine(10, 0, 10, display.height() - 5, SSD1306_WHITE);
        display.drawLine(display.width() / 2, 0, display.width() / 2, display.height() - 25, SSD1306_WHITE);
        display.drawLine(display.width() - 1, 0, display.width() - 1, display.height() - 5, SSD1306_WHITE);
        display.drawLine(display.width() - 11, 0, display.width() - 11, display.height() - 5, SSD1306_WHITE);
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        for (int optionsIterator = 0; optionsIterator < 6; optionsIterator++, y += 10)
        {
            display.setCursor(x, y);                      // Set the cursor position . The top left position is 0,0
            display.println(PIDoptions[optionsIterator]); // Print from the cursor position
            if (optionsIterator < 4)
            {
                display.setCursor(display.width() / 2 + 4, y);
                display.println(motorVariables[optionsIterator]);
            }
        }
    }
    else if (menuType == "SENSOR_MENU")
    {
        // Drawing the gridlines
        display.drawLine(0, 0, 0, display.height() - 5, SSD1306_WHITE);
        display.drawLine(10, 0, 10, display.height() - 5, SSD1306_WHITE);
        display.drawLine(display.width() - 1, 0, display.width() - 1, display.height() - 5, SSD1306_WHITE);

        // drawing the options
        display.setTextSize(1);              // Set the text size
        display.setTextColor(SSD1306_WHITE); // Set the text color

        // Push all the options to the display buffer
        for (int optionsIterator = 0; optionsIterator < 6; optionsIterator++, y += 10)
        {
            display.setCursor(x, y);                             // Set the cursor position . The top left position is 0,0
            display.println(sensorMenuOptions[optionsIterator]); // Print from the cursor position
        }
    }
    else if (menuType == "SENSOR_THRESHOLD_MENU")
    {
        display.drawLine(0, 0, 0, display.height() - 5, SSD1306_WHITE);
        display.drawLine(10, 0, 10, display.height() - 5, SSD1306_WHITE);
        display.drawLine(display.width() / 2, 0, display.width() / 2, display.height() - 5, SSD1306_WHITE);
        display.drawLine(display.width() - 1, 0, display.width() - 1, display.height() - 5, SSD1306_WHITE);
        display.drawLine(display.width() - 11, 0, display.width() - 11, display.height() - 5, SSD1306_WHITE);
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        for (int optionsIterator = 0; optionsIterator < numOfSensors / 2; optionsIterator++, y += 10)
        {
            display.setCursor(x, y);                           // Set the cursor position . The top left position is 0,0
            display.println(sensorThreshold[optionsIterator]); // Print from the cursor position
            display.setCursor(display.width() / 2 + 4, y);
            display.println(sensorThreshold[(numOfSensors - 1) - optionsIterator]);
        }
    }
    else if (menuType == "SENSOR_RAW_MENU")
    {
        display.drawLine(0, 0, 0, display.height() - 5, SSD1306_WHITE);
        display.drawLine(10, 0, 10, display.height() - 5, SSD1306_WHITE);
        display.drawLine(display.width() / 2, 0, display.width() / 2, display.height() - 5, SSD1306_WHITE);
        display.drawLine(display.width() - 1, 0, display.width() - 1, display.height() - 5, SSD1306_WHITE);
        display.drawLine(display.width() - 11, 0, display.width() - 11, display.height() - 5, SSD1306_WHITE);
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        for (int optionsIterator = 0; optionsIterator < numOfSensors / 2; optionsIterator++, y += 10)
        {
            display.setCursor(x, y);                            // Set the cursor position . The top left position is 0,0
            display.println(sensorRawReading[optionsIterator]); // Print from the cursor position
            display.setCursor(display.width() / 2 + 4, y);
            display.println(sensorRawReading[(numOfSensors - 1) - optionsIterator]);
        }
    }
    else if (menuType == "SENSOR_BINARY_MENU")
    {
        display.drawLine(0, 0, 0, display.height() - 5, SSD1306_WHITE);
        display.drawLine(10, 0, 10, display.height() - 5, SSD1306_WHITE);
        display.drawLine(display.width() / 2, 0, display.width() / 2, display.height() - 5, SSD1306_WHITE);
        display.drawLine(display.width() - 1, 0, display.width() - 1, display.height() - 5, SSD1306_WHITE);
        display.drawLine(display.width() - 11, 0, display.width() - 11, display.height() - 5, SSD1306_WHITE);
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        for (int optionsIterator = 0; optionsIterator < numOfSensors / 2; optionsIterator++, y += 10)
        {
            display.setCursor(x, y);                               // Set the cursor position . The top left position is 0,0
            display.println(sensorBinaryReading[optionsIterator]); // Print from the cursor position
            display.setCursor(display.width() / 2 + 4, y);
            display.println(sensorBinaryReading[(numOfSensors - 1) - optionsIterator]);
        }
    }
    display.display();
}

void displayOptionSelector(String menuType)
{
    optY = 2;
    String buttonInstruction;
    if (menuType == "MAIN_MENU")
    {
        display.drawRect(optX, optY, optH, optH, SSD1306_WHITE);
        display.fillRect(optX, optY, optH, optH, SSD1306_WHITE);
        display.display();
        while (true)
        {
            buttonInstruction = buttonPressed();
            if (buttonInstruction != "NO")
            {

                if (buttonInstruction == "BTN_UP" && (optY + 10) && (optY - 10) >= 2)
                {
                    optY -= 10;
                }
                else if (buttonInstruction == "BTN_DOWN" && (optY + 10) < display.height() - 10)
                {
                    optY += 10;
                }
                else if (buttonInstruction == "BTN_SELECT" && optY >= 2 && optY <= display.height() - 10)
                {
                    // if (mainMenuOptions[optY / 10] == "RUN")
                    // {
                    //     display.clearDisplay();
                    //     display.display();
                    //     while (true)
                    //     {
                    //         Run();
                    //         if (buttonPressed() != "NO")
                    //             break;
                    //     }
                    // }
                    displayMenu(mainMenuOptions[optY / 10]);
                }
                displayDrawMenu("MAIN_MENU");
                display.drawRect(optX, optY, optH, optH, SSD1306_WHITE);
                display.fillRect(optX, optY, optH, optH, SSD1306_WHITE);
                display.display();
                delay(300);
            }
        }
    }
    else if (menuType == "PID_MENU")
    {
        display.drawRect(optX, optY, optH, optH, SSD1306_WHITE);
        display.fillRect(optX, optY, optH, optH, SSD1306_WHITE);
        display.drawRect((SCREEN_WIDTH - 11 + optX), optY, optH, optH, SSD1306_WHITE);
        display.fillRect((SCREEN_WIDTH - 11 + optX), optY, optH, optH, SSD1306_WHITE);
        display.display();
        while (true)
        {
            buttonInstruction = buttonPressed();
            if (buttonInstruction != "NO")
            {

                if (buttonInstruction == "BTN_UP" && (optY + 10) && (optY - 10) >= 2)
                {
                    optY -= 10;
                }
                else if (buttonInstruction == "BTN_DOWN" && (optY + 10) < display.height() - 10)
                {
                    optY += 10;
                }
                else if (buttonInstruction == "BTN_LEFT" && optY / 10 < 4)
                {
                    motorVariables[optY / 10] -= 0.2;
                }
                else if (buttonInstruction == "BTN_RIGHT" && optY / 10 < 4)
                {
                    motorVariables[optY / 10] += 0.2;
                }
                else if (buttonInstruction == "BTN_SELECT" && optY >= 2 && optY <= display.height() - 10)
                {
                    if (strcmp(PIDoptions[optY / 10], "BACK") == 0)
                    {
                        delay(300);
                        return;
                    }
                    else
                    {
                        optionHandler(PIDoptions[optY / 10]);
                        delay(300);
                    }
                }
                displayDrawMenu("PID_MENU");
                display.drawRect(optX, optY, optH, optH, SSD1306_WHITE);
                display.fillRect(optX, optY, optH, optH, SSD1306_WHITE);
                display.drawRect((SCREEN_WIDTH - 11 + optX), optY, optH, optH, SSD1306_WHITE);
                display.fillRect((SCREEN_WIDTH - 11 + optX), optY, optH, optH, SSD1306_WHITE);
                display.display();
                delay(300);
            }
        }
    }
    else if (menuType == "SENSOR_MENU")
    {
        display.drawRect(optX, optY, optH, optH, SSD1306_WHITE);
        display.fillRect(optX, optY, optH, optH, SSD1306_WHITE);
        display.display();
        while (true)
        {
            buttonInstruction = buttonPressed();
            if (buttonInstruction != "NO")
            {

                if (buttonInstruction == "BTN_UP" && (optY + 10) && (optY - 10) >= 2)
                {
                    optY -= 10;
                }
                else if (buttonInstruction == "BTN_DOWN" && (optY + 10) < display.height() - 10)
                {
                    optY += 10;
                }
                else if (buttonInstruction == "BTN_SELECT" && optY >= 2 && optY <= display.height() - 10)
                {
                    if (strcmp(sensorMenuOptions[optY / 10], "BACK") == 0)
                    {
                        delay(300);
                        return;
                    }
                    else
                    {
                        optionHandler(sensorMenuOptions[optY / 10]);
                        delay(300);
                    }
                }
                displayDrawMenu("SENSOR_MENU");
                display.drawRect(optX, optY, optH, optH, SSD1306_WHITE);
                display.fillRect(optX, optY, optH, optH, SSD1306_WHITE);
                display.display();
                delay(300);
            }
        }
    }
}

void displayScrollText(void)
{
    display.clearDisplay();

    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 0);
    display.println(F("scroll"));
    display.display(); // Show initial text
    delay(100);

    // Scroll in various directions, pausing in-between:
    display.startscrollright(0x00, 0x0F);
    delay(2000);
    display.stopscroll();
    delay(1000);
    display.startscrollleft(0x00, 0x0F);
    delay(2000);
    display.stopscroll();
    delay(1000);
    display.startscrolldiagright(0x00, 0x07);
    delay(2000);
    display.startscrolldiagleft(0x00, 0x07);
    delay(2000);
    display.stopscroll();
    delay(1000);
}
