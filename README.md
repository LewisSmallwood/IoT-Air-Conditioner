# IoT Air Conditioner
My internet-connected portable air conditioning unit with power, speed, and temperature controls via a HTTP API.

## Brief
This project is a hardware and software solution that allows the existing functions of a portable air conditioner to be controlled over the Internet.

The air conditioning unit has buttons on it to control power, speed, operating modes, temperature, and the timer function.

I wanted to be able to control these functions over the internet, so I could turn on and off the unit from my phone.

The air conditioning unit used for the project was an Arlec 5000 BTU portable air conditioner, but the same implementation can be used for all air conditioners.

## Hardware
To enable the control of the unit over the internet, an ESP8266 microcontroller was used which is a low-cost WiFi connected microcontroller.

The controller was wired up to the push buttons on the control panel of the air conditioner.

This configuration allowed the existing push buttons on the control panel to be controlled from the board.

Each button was wired up to its own digital output pin on the controller.

Rather than using relays to toggle the buttons, opto-isolators were used to avoid annoying clicking sounds.

### Circuit
Here is the wiring:

![Circuit Wiring](https://bespoke.dev/assets/images/projects/iot-air-con/1.png)

The buttons on the panel are still usable externally:

![Control Panel](https://bespoke.dev/assets/images/projects/iot-air-con/4.png)

## Software
### Environment Variables
An environment variables file is included in the project.

An example of this file is provided in the repository (called `example-environment.h`).
This file should be renamed to `environment.h` and populated in the project.

It contains specific configuration details for your project, including WiFi passwords, and details of control pins.

To specify the network credentials you wish to use, the network credentials list can be modified in the `environment.h` file as follows:

```
const Network network_credentials[] = {
  { "YOUR_SSID_1", "YOUR_PASSWORD_1" },
  { "YOUR_SSID_2", "YOUR_PASSWORD_2" },
};
```

### Control API
The endpoints on the API are also configured within the `environment.h` file.

A list of buttons is defined which specified what endpoints are available, and which control pin should be toggled when the HTTP endpoint is called.

The button list is defined as follows, and can be modified to implement any functions:
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

This list above results in the following endpoints being available:
* http://ipaddress/power
* http://ipaddress/speed
* http://ipaddress/mode
* http://ipaddress/eco
* http://ipaddress/time
* http://ipaddress/up
* http://ipaddress/down

When making a web request to any of these endpoints, the microcontroller will simulate a press of the button using the control pin specified for the endpoint.
