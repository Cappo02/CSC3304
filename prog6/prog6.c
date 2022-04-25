/**
* This program reads in text from a given input file that contains information about
* several types of vehicles and outputs the information in a formatted manner to a 
* given output file. The program will output certain specific information depending 
* on which type of vehicle is being input.
*
* CSC 3304 Programming project No 6
*
* @author Nicholas Caplette
* @since 3/29/22
*
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "prog6_functions.h"

int main(int argc, char const *argv[]) {
	
	//Enumeration of the different types of vehicles
	enum vehicle {car, truck, boat};
	//File used to read in information from
	FILE* vehicleFile;
	//File used to output information to
	FILE* outFile;
	//String used to check which type of vehicle is being input
	char inStr[MAX_LENGTH];
	//Array of inputted vehicles
	VehicleTypes *(vehicleList[MAX_VEHICLES]);
	//Counter to see which index you are inputting into
	int index;

	//Opens the input and output files and initializes index counter
	vehicleFile = fopen("./TestInput.txt", "r");
	outFile = fopen("./out.txt", "w");
	index = 0;

	//Checks to see if you are at the end of the file
	while(fgets(inStr, MAX_LENGTH, vehicleFile) != NULL) {

		//Mallocs vehicle that is about to be input
		vehicleList[index] = (VehicleTypes *)malloc(sizeof(VehicleTypes));

		//If statement tree used to see which type of vehicle is being read in
		if(!strcmp(inStr, "car\n")) {

			//If the read in string is "car", the type is set to car
			vehicleList[index]->type = car;

		} else if(!strcmp(inStr, "truck\n")) {

			//If the read in string is "truck", the type is set to truck
			vehicleList[index]->type = truck;

		} else if(!strcmp(inStr, "boat\n")) {

			//If the read in string is "boat", the type is set to boat
			vehicleList[index]->type = boat;

		}

		//Inputs a vehicle into the array based on what type of vehicle is read in.
		switch(vehicleList[index]->type) {

			case 0:
				//If the type is car, the car's make, model, year, VIN, number of doors, and rear configuration are read in
				//and stored in the appropriate variables.
				InputCar(vehicleFile, MAX_LENGTH, vehicleList[index]->Vehicles.car.make, vehicleList[index]->Vehicles.car.model, &vehicleList[index]->year, 
				vehicleList[index]->yearString, vehicleList[index]->Vehicles.car.vin, &vehicleList[index]->Vehicles.car.numDoors, 
				vehicleList[index]->Vehicles.car.numDoorsString, vehicleList[index]->Vehicles.car.rearConfig);
				break;

			case 1:
				//If the type is truck, the truck's make, model, year, VIN, number of doors, and towing capacity are read in 
				//and stored in the appropriate variables. 
				InputTruck(vehicleFile, MAX_LENGTH, vehicleList[index]->Vehicles.truck.make, vehicleList[index]->Vehicles.truck.model, &vehicleList[index]->year, 
				vehicleList[index]->yearString, vehicleList[index]->Vehicles.truck.vin, &vehicleList[index]->Vehicles.truck.numDoors, 
				vehicleList[index]->Vehicles.truck.numDoorsString, &vehicleList[index]->Vehicles.truck.towCap, vehicleList[index]->Vehicles.truck.towCapString);
				break;

			case 2:
				//If the type is boat, the boat's make, model, year, VIN, and motor type are read in and stored in the
				//appropriate variables.
				InputBoat(vehicleFile, MAX_LENGTH, vehicleList[index]->Vehicles.boat.make, vehicleList[index]->Vehicles.boat.model, &vehicleList[index]->year, 
				vehicleList[index]->yearString, vehicleList[index]->Vehicles.boat.vin, vehicleList[index]->Vehicles.boat.motorType);
				break;

		}

		//Increases index within array that will be used on the next pass if there is a next vehicle.
		index++;

	}

	//Bubble sorts vehicle list array.
	bubbleSort(vehicleList, index - 1);

	//Prints out all vehciles in array based on which type of vehicle they are.
	for(int i = 0; i < index; i++) {
		
		switch(vehicleList[i]->type) {
			
			case 0:
				OutputCar(outFile, vehicleList[i]->Vehicles.car.make, vehicleList[i]->Vehicles.car.model, vehicleList[i]->year, 
				vehicleList[i]->Vehicles.car.vin, vehicleList[i]->Vehicles.car.numDoors, vehicleList[i]->Vehicles.car.rearConfig);
				break;

			case 1:
				OutputTruck(outFile, vehicleList[i]->Vehicles.truck.make, vehicleList[i]->Vehicles.truck.model, vehicleList[i]->year, 
				vehicleList[i]->Vehicles.truck.vin, vehicleList[i]->Vehicles.truck.numDoors, vehicleList[i]->Vehicles.truck.towCap);
				break;

			case 2:
				OutputBoat(outFile, vehicleList[i]->Vehicles.boat.make, vehicleList[i]->Vehicles.boat.model, vehicleList[i]->year, 
				vehicleList[i]->Vehicles.boat.vin, vehicleList[i]->Vehicles.boat.motorType);
				break;

		}

	}

	//Frees entire vehicle list array
	for(int i = 0; i < index; i++) {

		free(vehicleList[i]);

	}

	//Closes the input and output files
	fclose(vehicleFile);
	fclose(outFile);

	return 0;
	
}
