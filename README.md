# Introduction

This VST Plugin addresses the need for the automation of [SoundScapeRenderer (SSR)](http://spatialaudio.net/ssr/) scenes from a [Digital Audio Workstation (DAW)](https://en.wikipedia.org/wiki/Digital_audio_workstation).

The SSRemote VST plugin was developed for Linux and tested with the [Ardour DAW](http://ardour.org/). Since the Plugin was developed in the light of cross-platform compatibility it also can run under other Operating Systems (OS) such as OSX and other DAWs (Reaper, Ableton and Logic).

Since this is a <b>experimental open source project</b>, any contributions are very much welcome!

# Installation

Please read the [installation guide](https://github.com/rodrigodzf/SSRemoteVST/blob/master/INSTALLATION.md).

# Configuration

## Environment Variables

Please set the environment variables as follows, since the following environment variables are not only needed for compilation but also at runtime:

  The directory/location of the Steinberg VST3 SDK:

  ```bash
  # Steinberg VST3 Audio Plug-Ins SDK
  export VST3_SDK=/path/to/VST3SDK
  ```

  The directory/location of the SSRemote VST:

  ```bash
  # SSRemote VST
  export SSREMOTE_VST=/path/to/ssremote_vst
  ```

  The directory/location of the JUCE Framework located in the SSRemote VST:

  ```bash
  # SSRemote VST JUCE Framework
  export JUCE_LIB_CODE=$SSREMOTE_VST/JUCE
  ```

## XML Configuration File

The VST Plugin requires a config file to successfully establish a TCP/IP connection to the SSR. The user has to create a file called <b>ssremote_config.xml</b> with the following content:

```XML
<?xml version="1.0" encoding="utf-8"?>
<config>
  <network>
    <host>localhost</host>
    <port>4711</port>
    <timeout>1000</timeout>
  </network>
</config>
```

| Markup | Description |
| ------:|:------------|
|network|the network configuration|
|host   |the host on which the SSR is running|
|port   |the port on which the SSR is listening for incoming TCP/IP requests|
|timeout|the time in milliseconds the VST Plugin waits for an answer by the SSR|

The contents of the markups host, port and timeout are just examples which the user may edit regarding his systems and SSR configuration.

# General Information

## Running the VST Plugin

To remotly control the SSR scene from the Plugin the user has to do the following:

1. Start the JACK Audio Connection Kit
2. Start the SSR and load a scene
3. Start the DAW and load the SSRemote VST Plugin

## Description of the GUI

The VST Plugins GUI is generally splitted in two sections. The <b>General Controls</b> section and the <b>Source Controls</b> section.

### General Controls

|Name       |GUI Element|Description|
|:---------:|:---------:|:---------:|
|Connect    |Button     |connects or disconnects the connection to the SSR|
|New Source |Button     |creates a new source with default values for the parameters|

### Source Controls

|Name       |GUI Element|Description|
|:---------:|:---------:|:---------:|
|Source     |Dropdown   |select a source for manipulation|
|Name       |Textfield  |read and writeable textfield for the name of the source|
|Jackport   |Dropdown   |select the jackport the source shall connect to|
|Model      |Dropdown   |select the type of model of the source|
|Azimuth    |Textfield  |readable only textfield for displaying the sources orientation|
|Mute       |Button     |mutes and unmutes the source|
|Fix        |Button     |fix and unfix the source position|
|Gain       |Slider     |adjust the gain of the source in dB|
|Source Control Pad|2D Pad|displayes the sources position|
|Zoom       |Buttons    |zooms in and out the Source Control Pad|
|Scale Reference|-      |displays a scale reference in meter for the Source Control Pad|
|X Position |Slider     |controller for the X position of the source|
|Y Position |Slider     |controller for the Y position of the source|

## Automatable Parameters

The Host (DAW) is able to automate the following parameters:

+ X Position
+ Y Position
+ Gain
+ Mute
+ Model
+ Fixed

## Logfiles

The Plug-In logs will be written to the file ```log.txt```, located in the root directory.<br/>
The logs will look as follows:

```
[YYYY-MM-DD HH:mm:SS] [<LOGTYPE>] <Log text>
```

# License

[GNU GENERAL PUBLIC LICENSE](http://www.gnu.org/licenses/gpl-3.0.de.html)<br/>
Version 3, 29 June 2007

Copyright © 2015<br/>
Quality and Usability Lab<br7/>
Berlin Institute of Technology<br/>
http://www.qu.tu-berlin.de/<br/>

For more detailed information, please read the license.txt in the root directory.
