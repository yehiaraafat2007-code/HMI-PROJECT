
# Embedded Systems Project Report: Temperature Monitoring and Alarm System

## 1. Introduction

In this project, we made a temperature monitoring system using an Arduino UNO and an LM35 temperature sensor.

The temperature is displayed on a 16x2 LCD. We used two buttons to increase the lower limit (LL) and higher limit (LH).

If the temperature goes below LL or above LH, the LED and buzzer turn ON and the LCD shows NOK.

If the temperature is within the limits, the LED and buzzer stay OFF and the LCD shows OK.

We also used a 10k potentiometer to adjust the LCD contrast.

## 2. Project Code

**GitHub Repository:**

[submission_repo](https://github.com/yehiaraafat2007-code/HMI-PROJECT)

**Local Root Directory:**

[project_code](./)

**Main Program:**

[main_code](./main.ino)

## 3. Test Cases

Test cases are written using Robot Framework.

[robot_tests](./testcases2_corrected.robot)

## 4. Bill of Materials (BOM)

**BOM:**

[bom_file](./bom%202.csv)

**Optimized BOM:**

[optimized_bom_file](./optimized_bom%202.csv)

## 5. Video Demonstration

[recorded_video](./video.mp4)

## 6. Design

[design_document](./design%20HMI.md)
