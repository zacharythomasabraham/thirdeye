# thirdeye

Github:https://github.com/zacharythomasabraham/thirdeye

Requirements:
Arduino
ESP8266 Wifi Module
DSi8B20 Temperature sensor
Xcode 
Twilio api
Sketch
Python Web Server on the cloud

Connect Arduino,DSi8B20 Temperature sensor,ESP8266 Wifi Module and load the code under Arduino into Sketch.You now have the IOT unit for the home working

Now Load the Xcode project under IOS folder in a simulator

Deploy the server1 code to Azure and Launch Python web server
https://docs.microsoft.com/en-us/azure/app-service/app-service-web-get-started-python

Heath check:
You can use a url like https://thirdiy.azurewebsites.net/alert/18178217752/167 to test the Azure server where 18178217752 is the phone number to send if the server is up and running

Example  test:

Now set the threshold to 97 degree on the IOS app.Now boil water next to the IOT unit.You’ll see messages go from home unit to python server and then twill.You’ll receive a voice message and SMS with Temperature sensed by the unit.

