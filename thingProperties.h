#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[] = "236d02aa-4d29-4cb0-958f-1dbf058595f9";

const char SSID[] = SECRET_SSID;
const char PASS[] = SECRET_OPTIONAL_PASS;

const char DEVICE_KEY[] = SECRET_DEVICE_KEY;


namespace cloud {

  float humidity;
  float light;
  float moisture;
  float temperature;
  bool pump;

  void onPumpChange();
};

void initProperties() {

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(cloud::humidity, READ, 5 * SECONDS, NULL);
  ArduinoCloud.addProperty(cloud::light, READ, 5 * SECONDS, NULL);
  ArduinoCloud.addProperty(cloud::moisture, READ, 5 * SECONDS, NULL);
  ArduinoCloud.addProperty(cloud::temperature, READ, 5 * SECONDS, NULL);
  ArduinoCloud.addProperty(cloud::pump, READWRITE, 5 * SECONDS, cloud::onPumpChange);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
