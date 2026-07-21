// Fill in your Blynk Template info (found in your Blynk Dashboard)
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_DEVICE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

// Comment out this line to disable print messages in Serial Monitor
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

// GPIO Pin assignments according to project schema
const int FACULTY_BUTTON_PIN = 27; // Pin assigned to Faculty button
const int STUDENT_BUTTON_PIN = 14; // Pin assigned to Student button

// State variables to handle button press events and prevent repeated spamming
bool facultyPressed = false;
bool studentPressed = false;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Set pin modes using internal pull-up resistors
  // Buttons connect GPIO -> GND when pressed (LOW state)
  pinMode(FACULTY_BUTTON_PIN, INPUT_PULLUP);
  pinMode(STUDENT_BUTTON_PIN, INPUT_PULLUP);

  // Initialize Blynk connection
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  // Keep Blynk connected and processing incoming/outgoing messages
  Blynk.run();

  // Read current button states
  int facultyState = digitalRead(FACULTY_BUTTON_PIN);
  int studentState = digitalRead(STUDENT_BUTTON_PIN);

  // --- FACULTY BUTTON LOGIC ---
  if (facultyState == LOW && !facultyPressed) {
    Serial.println("Faculty button pressed!");
    // Log event configured in Blynk Cloud
    Blynk.logEvent("faculty_waiting", "FACULTY is waiting outside");
    facultyPressed = true;
    delay(50); // Simple debouncing delay
  } 
  else if (facultyState == HIGH && facultyPressed) {
    facultyPressed = false; // Reset status on button release
  }

  // --- STUDENT BUTTON LOGIC ---
  if (studentState == LOW && !studentPressed) {
    Serial.println("Student button pressed!");
    // Log event configured in Blynk Cloud
    Blynk.logEvent("student_waiting", "STUDENT is waiting outside");
    studentPressed = true;
    delay(50); // Simple debouncing delay
  } 
  else if (studentState == HIGH && studentPressed) {
    studentPressed = false; // Reset status on button release
  }
}
