# Project Runner
An android game for class

## Dependencies
JDK 8

Android NDK

Apache Ant

Android SDK Manager:

	Android 4.0.3:

		SDK Platform

		* System Images <- recominded

Make sure the NDK, Ant, and AndroidSDK-platform-tools are in you Path environment variable (example: C:\AndroidDevelopment\android-ndk-r10e;C:\AndroidDevelopment\apache-ant-1.9.6\bin;C:\AndroidSDK\platform-tools)

Make sure the JAVA_HOME environment variable points to the JDK folder (example: C:\Program Files\Java\jdk1.8.0_45)

Make sure the ANDROID_HOME environment variable points to the android-sdk-windows folder (example: C:\AndroidSDK)

## How to build
`ndk-build`

`ant debug install`

## Libraries
SDL2

Google Play Game Services

## Specifications
Procedural endless level

3 lanes

Turning right and left

Random obsticles you must avoid

Leaderboard local and global