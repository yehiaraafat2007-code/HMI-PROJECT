*** Settings ***
Documentation    Temperature Monitoring System - Manual Hardware Tests
Library          Dialogs
Library          BuiltIn

*** Keywords ***
Check Hardware Result
    [Arguments]    ${instructions}    ${expected}
    Log    Instructions: ${instructions}
    Log    Expected: ${expected}
    ${result}=    Get Selection From User    ${instructions}\n\nEXPECTED:\n${expected}\n\nCheck the Arduino, then select PASS or FAIL.    PASS    FAIL
    Should Be Equal As Strings    ${result}    PASS    Hardware did not match the expected result.

*** Test Cases ***
Test Case 1 - System Startup
    [Documentation]    Check the starting temperature limits.
    # Arrange: Connect Arduino, LM35, LCD, buttons, LED and buzzer.
    # Act: Switch on or reset the Arduino.
    # Assert: LCD shows the temperature, LL 20 and LH 35.
    Check Hardware Result    Connect the components and switch on or reset the Arduino.    LCD shows temperature, LL:20 and LH:35.

Test Case 2 - Normal Temperature
    [Documentation]    Check temperature inside the limits.
    # Arrange: LL 20, LH 35.
    # Act: Keep sensor near 25 C.
    # Assert: LCD OK, LED OFF, buzzer OFF.
    Check Hardware Result    Reset the Arduino and keep the sensor near 25 C.    LCD shows OK. LED and buzzer are OFF.

Test Case 3 - High Temperature
    [Documentation]    Check the high temperature alarm.
    # Arrange: LL 20, LH 35.
    # Act: Raise sensor temperature above 35 C safely.
    # Assert: LCD NOK, LED ON, buzzer ON.
    Check Hardware Result    Reset the Arduino and safely raise LM35 temperature above 35 C.    LCD shows NOK. LED and buzzer are ON.

Test Case 4 - Low Temperature
    [Documentation]    Check the low temperature alarm.
    # Arrange: LL 20, LH 35.
    # Act: Cool the sensor below 20 C safely.
    # Assert: LCD NOK, LED ON, buzzer ON.
    Check Hardware Result    Reset the Arduino and safely cool the LM35 below 20 C.    LCD shows NOK. LED and buzzer are ON.

Test Case 5 - Increase Lower Limit
    [Documentation]    Check the LL button.
    # Arrange: LL 20, LH 35.
    # Act: Press LL once.
    # Assert: LL becomes 21.
    Check Hardware Result    Reset the Arduino and press the LL button once.    LCD displays LL:21.

Test Case 6 - Increase Higher Limit
    [Documentation]    Check the LH button.
    # Arrange: LL 20, LH 35.
    # Act: Press LH once.
    # Assert: LH becomes 36.
    Check Hardware Result    Reset the Arduino and press the LH button once.    LCD displays LH:36.

Test Case 7 - Lower Limit Protection
    [Documentation]    LL must stay below LH.
    # Arrange: Get LL to 34 with LH 35.
    # Act: Press LL again.
    # Assert: LL remains 34.
    Check Hardware Result    Reset Arduino, increase LL to 34, then press LL again.    LL stays 34, below LH 35.

Test Case 8 - Maximum Higher Limit
    [Documentation]    LH must not go above 99 C.
    # Arrange: Get LH to 99.
    # Act: Press LH again.
    # Assert: LH remains 99.
    Check Hardware Result    Reset Arduino, increase LH to 99, then press LH again.    LCD still shows LH:99.

Test Case 9 - Temperature At The Limits
    [Documentation]    Check alarm at exactly LL and LH.
    # Arrange: LL 20 and LH 35.
    # Act: Set measured temperature to exactly 20 then 35 C.
    # Assert: Both show OK with alarm OFF.
    Check Hardware Result    Reset Arduino and check the measured temperatures at exactly 20 C and 35 C.    Both values show OK. LED and buzzer are OFF.

Test Case 10 - Alarm Returns To Normal
    [Documentation]    Check alarm turns off when temperature returns to normal.
    # Arrange: LL 20 and LH 35.
    # Act: Raise temperature above 35 C then return near 25 C.
    # Assert: NOK becomes OK, LED and buzzer turn OFF.
    Check Hardware Result    Reset Arduino. Heat sensor above 35 C, then let it cool to about 25 C.    LCD changes NOK to OK. LED and buzzer turn OFF.
