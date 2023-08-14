/**************************************************************************************************
 Project     : Vehicle Control System
 Author      : Nouran Ahmed Kamel
 Created on  : Aug 11, 2023
 **************************************************************************************************/
#include <stdio.h>
#define WITH_ENGINE_TEMP_CONTROLLER 1
typedef enum {
	false, true // Making boolean Data type
} bool;
// Vehicle Data
struct VehicleData {
	bool EngineState;
	bool AC;
	unsigned int vehicleSpeed;
	int RoomTemperature;
#if(WITH_ENGINE_TEMP_CONTROLLER == 1)
	bool EngineTemperatureControllerState;
	int EngineTemperature;
#endif
};
/* Function prototypes */
void StartupOutput(char *input, struct VehicleData *vehicleData);
void StartupFunction(char returnedValue, struct VehicleData *vehicleData);
void SensorsSetMenuOutput(char *SensorsSetMenuInput);
void SensorsSetMenuFunction(char returnedValueFromSetMenu,
		struct VehicleData *vehicleData);
void TrafficlightdataFunction(char *SettingTrafficLightData,
		struct VehicleData *vehicleData);
void temperaturedataFunction(int *Settingtemperaturedata,
		struct VehicleData *vehicleData);
#if(WITH_ENGINE_TEMP_CONTROLLER == 1)
void EnginetemperaturedataFunction(int *SettingEnginetemperaturedata,
		struct VehicleData *vehicleData);
#endif
void VehichleSpeedAt30(struct VehicleData *vehicleData);
void printVehicleData(struct VehicleData *vehicleData);
//***********************

int main(void) {
	setbuf(stdout, NULL);

#if(WITH_ENGINE_TEMP_CONTROLLER == 1)
	struct VehicleData data = { true, false, 35, 40, false, 90 };
#else
	struct VehicleData data = { true, false, 35, 40};
#endif
//	struct VehicleData *pointerTodata = &data;   // Not needed
	char input;
	StartupOutput(&input, &data);
	return 0;
}

/* Startup Output
 *****************
 This allows the function to modify the value of input by taking it from user in the
 main function and making pointer to struct in order to update the values of struct.
 ("Pass by reference") */
void StartupOutput(char *input, struct VehicleData *vehicleData) {
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n\n");
	scanf(" %c", input);
	StartupFunction(*input, vehicleData);
}

// Startup Function
void StartupFunction(char returnedValue, struct VehicleData *vehicleData) {
	char returnedValueInStartup;
	switch (returnedValue) {
	case 'a':
		printf("Turning on the vehicle engine\n\n");
		SensorsSetMenuOutput(&returnedValueInStartup);
		SensorsSetMenuFunction(returnedValueInStartup, vehicleData);
		break;
	case 'b':
		printf("Turning off the vehicle engine\n\n");
		StartupOutput(&returnedValueInStartup, vehicleData);
		break;
	case 'c':
		printf("Quitting the system\n");
		break;
	default:
		printf("Invalid input\n");
		break;
	}
}

// Sensors set menu
void SensorsSetMenuOutput(char *SensorsSetMenuInput) {
	printf("\na. Turn off the engine.\n");
	printf("b. Set the traffic light color.\n");
	printf("c. Set the room temperature (Temperature Sensor)\n");
#if(WITH_ENGINE_TEMP_CONTROLLER == 1)
	printf("d. Set the engine temperature (Engine Temperature Sensor)\n\n");
#endif
	scanf(" %c", SensorsSetMenuInput);
}

// Sensors set menu Function
void SensorsSetMenuFunction(char returnedValueFromSetMenu,
		struct VehicleData *vehicleData) {
	char returnedValueOfTurningoffEngineOrSettingTraffic;
	int returnedValueFromSettingtempOrEnginetemp;
	switch (returnedValueFromSetMenu) {
	case 'a':
		printf("Turning off the engine.\n\n");
		StartupOutput(& returnedValueOfTurningoffEngineOrSettingTraffic, vehicleData);
		break;
	case 'b':
		printf("Setting the traffic light color.\n");
		TrafficlightdataFunction(& returnedValueOfTurningoffEngineOrSettingTraffic, vehicleData);
		break;
	case 'c':
		printf("Setting the room temperature (Temperature Sensor)\n");
		temperaturedataFunction(&returnedValueFromSettingtempOrEnginetemp, vehicleData);
		break;
#if(WITH_ENGINE_TEMP_CONTROLLER == 1)
	case 'd':
		printf("Setting the engine temperature (Engine Temperature Sensor)\n\n");
		EnginetemperaturedataFunction(&returnedValueFromSettingtempOrEnginetemp,
				vehicleData);
		break;
#endif
	default:
		printf("Invalid input\n");
		break;
	}
}

// Traffic light data Function
void TrafficlightdataFunction(char *SettingTrafficLightData,
		struct VehicleData *vehicleData) {
	char returnedValue;
	scanf(" %c", SettingTrafficLightData);
	switch (*SettingTrafficLightData) {
	case 'g':
	case 'G':
		vehicleData->vehicleSpeed = 100;
		break;
	case 'o':
	case 'O':
		vehicleData->vehicleSpeed = 30;
		VehichleSpeedAt30(vehicleData);
		break;
	case 'r':
	case 'R':
		vehicleData->vehicleSpeed = 0;
		break;
	default:
		printf("Invalid input\n");
		break;
	}
	printVehicleData(vehicleData);
	SensorsSetMenuOutput(&returnedValue);
	SensorsSetMenuFunction(returnedValue, vehicleData);
}

// Room temperature data Function
void temperaturedataFunction(int *Settingtemperaturedata,
		struct VehicleData *vehicleData) {
	char returnedValue;
	scanf(" %d", Settingtemperaturedata);
	if (*Settingtemperaturedata <= 10 || *Settingtemperaturedata >= 30) {
		vehicleData->RoomTemperature = 20;
		vehicleData->AC = true;
	} else {
		vehicleData->AC = false;
	}
	printVehicleData(vehicleData);
	SensorsSetMenuOutput(&returnedValue);
	SensorsSetMenuFunction(returnedValue, vehicleData);
}

// Engine temperature data Function
#if(WITH_ENGINE_TEMP_CONTROLLER == 1)
void EnginetemperaturedataFunction(int *SettingEnginetemperaturedata,
		struct VehicleData *vehicleData) {
	char returnedValue;
	scanf(" %d", SettingEnginetemperaturedata);
	if (*SettingEnginetemperaturedata <= 100
			|| *SettingEnginetemperaturedata >= 150) {
		vehicleData->EngineTemperature = 125;
		vehicleData->EngineTemperatureControllerState = true;
	} else {
		vehicleData->EngineTemperatureControllerState = false;
	}
	printVehicleData(vehicleData);
	SensorsSetMenuOutput(&returnedValue);
	SensorsSetMenuFunction(returnedValue, vehicleData);
}
#endif

//Vehicle Speed at 30km/hr
void VehichleSpeedAt30(struct VehicleData *vehicleData) {
	if (vehicleData->AC == false) {
		vehicleData->AC = true;
	}
	vehicleData->RoomTemperature = vehicleData->RoomTemperature
			* ((float) 5 / 4) + 1;
#if(WITH_ENGINE_TEMP_CONTROLLER == 1)
	if (vehicleData->EngineTemperatureControllerState == false) {
		vehicleData->EngineTemperatureControllerState = true;
	}
	vehicleData->EngineTemperature = vehicleData->EngineTemperature
			* ((float) 5 / 4) + 1;
#endif
}

// printVehicleData
void printVehicleData(struct VehicleData *vehicleData) {
	printf("Engine state: %s\n", vehicleData->EngineState ? "ON" : "OFF");
	printf("AC: %s\n", vehicleData->AC ? "ON" : "OFF");
	printf("Vehicle speed: %u km/hr\n", vehicleData->vehicleSpeed);
	printf("Room Temperature: %d C\n", vehicleData->RoomTemperature);
#if(WITH_ENGINE_TEMP_CONTROLLER == 1)
	printf("Engine Temperature Controller: %s\n",
			vehicleData->EngineTemperatureControllerState ? "ON" : "OFF");
	printf("Engine Temperature: %d C\n\n", vehicleData->EngineTemperature);
#endif
}
