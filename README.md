# IoT-Air-Conditioner
My internet-connected portable air conditioning unit with power, speed, and temperature controls via a HTTP API.

## Hardware
The code runs on an ESP8266 microcontroller. The controller is wired to the push buttons on the air conditioner control panel.

The existing push buttons on the control panel have been hooked into and wired into the microcontroller.

Rather than using relays to control the circuits, opto-isolators were used instead to avoid annoying clicking sounds.

Circuit diagram and pictures to follow.

## Software
### Environment Variables
To populate WiFi credentials in the project, an environment variables file is included in the project.
An example of this file is provided in the repository (called `example-environment.h`). This file should be renamed to `environment.h` and populated with the network credentials you wish to use.

The network credentials list is as follows:

```
const Network network_credentials[] = {
  { "YOUR_SSID_1", "YOUR_PASSWORD_1" },
  { "YOUR_SSID_2", "YOUR_PASSWORD_2" },
};
```

### Control API
The endpoints on the API are also configured within the `environment.h` file.

The list of buttons defines the available endpoints and what pins should be toggled when the HTTP endpoints are called.

The button list is as follows:
```
const Button buttons[] = {
  { "power", D1 },
  { "speed", D2 },
  { "mode", D3 },
  { "eco", D4 },
  { "time", D5 },
  { "up", D6 },
  { "down", D7 },
};
```

This would result in the following endpoints being available:
* http://ipaddress/power
* http://ipaddress/speed

When making a web request to any of these endpoints, the microcontroller will simulate a press of the button pin specified for the endpoint.
