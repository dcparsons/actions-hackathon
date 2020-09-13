# 2020 DEV.TO GitHub Actions Hackathon

This is my submission for the [DEV.TO GitHub Actions Hackathon](https://dev.to/devteam/announcing-the-github-actions-hackathon-on-dev-3ljn) that I have named "Noisy Build".  I entered this into the IoT category of the hackathon. 

# Summary
The premise of my entry is pretty simple: after a CI build completes, send a message to an Azure IoT Hub. That message is then relayed to a specific device (an [MXChip IoT DevKit](https://docs.microsoft.com/en-us/samples/azure-samples/mxchip-iot-devkit-get-started/sample/) in my case) that interprets the message and plays a sound based on whether or not the build succeeded or failed.  

The three main components of my entry follow.

 - **/src/web-app** - this is a vanilla dotnet API that was generated using `dotnet new webapi`. This is the code that the workflow will build and it is the result of this build that is sent to the IoT Hub. 
 - **/src/iot-app** - this is an Ardunio C++ project that has been loaded onto the MXChip.  This code is responsible for connecting to the IoT Hub, handling new messages, playing sounds, etc. 
     
      -  The `successSound.h` and `failureSound.h` files don't contain any worthwhile data so, as is, the iot-app has no sounds to play.  On my local these files contain the data that represents the `.wav`  files that get played when a message is received.  However, to avoid any distribution problems, I have checked these files in empty.  The references section explains how you can populate these files. 
 - **Workflow** - the CI workflow is fairly straight forward: as changes are made to `master` a `dotnet build` is run for the web-app defined above on an Ubuntu VM.  The result of the build causes the workflow to run [this action](https://github.com/dcparsons/azure-iot-action) which relays a message to an Azure IoT Hub.  

      - The hackathon urged contestants to use pre-existing workflows / actions for their entries, however the existing actions that existed for sending messages to an MQTT Hub would not work for me.  This is likely because Azure IoT Hub is [not a full feature MQTT Broker](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-mqtt-support). 

# Limitations
For this build, the only real limitations is what is available with the firmware and the amount of space you have available to you on the MXChip.  There is only around 1Mbyte of flash memory available on the MXChip so you need to be aware of that with your sound files otherwise you will run into `OutOfMemory` problems. 

Another problem I ran into (that I didn't have time to debug through) was there is some difference with playing a file during message callback versus playing the sound file via button press.  In my scenario, the code that played the success and failure sounds on button pressed worked as expected: the corresponding sound was played.  However when I adapted this to play a sound file based on the message that was received only the failure sound would play successfully.  I eventually just re-recorded the success sound into something smaller and that seemed to work.  While I suspect there was some memory issue, there was nothing apparent during my debugging. 


# References

Azure MXChip IoT DevKit - [Getting Started](https://docs.microsoft.com/en-us/samples/azure-samples/mxchip-iot-devkit-get-started/sample/)

Playing sound on an MXChip - [medium.com](https://medium.com/@johnkennedy_17457/playing-sound-files-on-the-az3166-mxchip-azure-iot-devkit-b99a0e5a9a90)

