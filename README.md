# 2ndYr_Assignment3_OralBearduino

"Success is no accident. It is hard work, perseverance, learning, studying,
sacrifice and most of all, love of what you are doing or learning to do. "
-Pele

## Infomercial Video of our Project

[![Video](http://img.youtube.com/vi/L_IXU5uO1O4/0.jpg)](https://www.youtube.com/watch?v=L_IXU5uO1O4&t=5s"Video")



## Group Details
| Name | Student No. | Student Email 
| --- | --- | --- |
| Jonathan Noble | C154879222 | c15487922@mydit.ie |
| Pia Ofalsa | C15734155 | c15734155@mydit.ie |

## Objective
For this project, our initial idea was to create a __notification system__ that can encourage and motivate children to brush their teeth in a fun, IoT(Internet of Things) environment. 


We then came up to the conclusion that we will use the platform of Arduino and develop an Android App which offers awesome IoT features - make sure to check down below for the full post about the features that are showcased in our project.


## Hardware Specs 
* __Usage of Genymotion Emulator for Android App__

* __Stuff Toy with the following hardware embodied__:
   *  TFT LCD Screen: 
      *  ![img_3417](https://cloud.githubusercontent.com/assets/18444618/25657799/8b7efa04-2ff7-11e7-839d-c56852fa35b4.JPG)
    
    * Arduino Uno
      * ![img_3424](https://cloud.githubusercontent.com/assets/18444618/25657861/d7437686-2ff7-11e7-818e-778fa2030904.JPG)
    
* __Wemos D1-mini with an ESP8266 WiFi Module__:
![img_3432](https://cloud.githubusercontent.com/assets/18444618/25657895/044f9736-2ff8-11e7-8752-721977766cfe.JPG)
  * Vibration Switch Sensor
  * Resistor
  * Jumper Wires
  * Breadboard
  

## Project Description
We divided the workload in two phases so we could learn both platforms at once. As a duo group, we thought the project per se was ambitious at first but we believe we managed to consider and tackle every necessary steps possible. 

With the objective in mind, our Android App - named after the project -  was made primarily for the parents to notify them once their children have used the toothbrush recently via a vibration switch sensor input read by Wemos D1-Mini with ESP8266. As for the kids' motivation counterpart, we decided to use a TFT LCD Screen embodied inside a stuff toy to display tips and advices and more importantly, a stop watch for the recommended two-minute duration of brushing.

## Goals
* Learning curve in both platforms
* Developing an Android App with fragments on a Navigation Bar
* Learn Arduino in C and C++; Arduino library functions
* Understanding the hardwares of TFT LCD screen i.e. Touchpoint and Wemos D1-Mini i.e. ESP8266 libraries
* Usage of base64 from base64encode.org for encoding username and password from the SMTP smtp2go.com server
* Git fetching-> merging/rebasing from an upstream branch was also another challenge in the beginning

## Features
* __Android App__:
  * Navigation Drawbar with Fragments:
    * Music Player on Home Page
    * E-mail Web View
    * Tutorial Page
    
    
  * App Screenshots:
  
      ![drawer](https://cloud.githubusercontent.com/assets/18444618/25658366/6ac5ae22-2ffa-11e7-92f6-0c6066334560.JPG)
      ![playmusic](https://cloud.githubusercontent.com/assets/18444618/25658368/6acaa364-2ffa-11e7-8ec7-6740983d6b32.JPG)
      ![email](https://cloud.githubusercontent.com/assets/18444618/25658367/6ac666e6-2ffa-11e7-8b78-7e3718481949.JPG)
      ![tut](https://cloud.githubusercontent.com/assets/18444618/25658365/6ac221a8-2ffa-11e7-9dbc-6d298329c59a.JPG)

* Wemos D1-Mini:
  * The controller uses the ESP8266 to send an email once the vibration switch sensor reads an analogue input
  * C/C++ header files used:
    - checkEmail.cpp/h consists of the responseCode to check availability of network. It also has the function to send the Email through the encoded SMTP username with the usage of base64. The screenshots provides the necessary requirements in underline to get the server connection to fully function. 

  * Wemos D1-Mini Procedure Screenshots:


![ser2](https://cloud.githubusercontent.com/assets/18444618/25829064/e50bdf3a-344b-11e7-8bbb-b9e984c9f848.png)
![ser1](https://cloud.githubusercontent.com/assets/18444618/25829065/e50c30b6-344b-11e7-9585-4165a8995346.png)

The generated base64 is then implemented in our code! Then voila! Magic is made by IoT!
![ser3](https://cloud.githubusercontent.com/assets/18444618/25829063/e506278e-344b-11e7-8ce1-dfa192f0d862.png)

* TFT LCD Screen
  * Tips & Advices on Splash Screens
  * Stop Watch for the recommended 2 minutes!
  * C/C++ header files used:
    - Buttons.cpp/h which creates/animates/activates/error-checks the buttons
    - Settings.cpp/h for the EEPROM library to save/reset/default values
    - Debug.h for debugging purposes
    - UI.cpp/h for the splash screens and the UI design of the screen

  * LCD Screen screenshots:

![img_0017](https://cloud.githubusercontent.com/assets/18444618/25666713/33d12d50-3019-11e7-880b-09b8921300f9.JPG)
![img_0019](https://cloud.githubusercontent.com/assets/18444618/25666709/33886700-3019-11e7-995f-7e99ad53199d.JPG)
![img_0018](https://cloud.githubusercontent.com/assets/18444618/25666708/33821102-3019-11e7-81bd-9df804d27bd4.JPG)
![img_0020](https://cloud.githubusercontent.com/assets/18444618/25666711/33a4f708-3019-11e7-9c90-a365008c7794.JPG)
![img_0021](https://cloud.githubusercontent.com/assets/18444618/25666712/33b2d2e2-3019-11e7-8eaa-3e6818151ce0.JPG)


## Conclusion & What we're proud of
We are very proud of getting out of our comfort zone. This year we learned how to make a scifi UI, a game and now something completely different and something that we believe in the future will make a huge impact on other people's lives, of course there is definitely room for improvement for this project but we can not wait to showcase it with more cool features.  

Runners experience a euphoria known as runners high. Programming definitely creates similar feeling. All those sleepless nights brainstorming for ideas, coding, debugging. 

It was a surreal experience to be able to put our knowledge into something useful.


