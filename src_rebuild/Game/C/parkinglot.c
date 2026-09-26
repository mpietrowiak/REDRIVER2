#include "driver2.h"
#include "parkinglot.h"

#include "mission.h"
#include "models.h"

#define PARKING_LOT_MAX_OBJECTS 48

int gCustomParkingLot = 0;

static CELL_OBJECT parkingLotObjects[PARKING_LOT_MAX_OBJECTS];
static int parkingLotObjectCount = 0;

static void AddParkingLotObject(int model, int x, int y, int z, int angle)
{
	CELL_OBJECT* object;

	if (model < 0 || parkingLotObjectCount >= PARKING_LOT_MAX_OBJECTS)
		return;

	object = &parkingLotObjects[parkingLotObjectCount++];
	object->pos.vx = x;
	object->pos.vy = y;
	object->pos.vz = z;
	object->pad = 0;
	object->yang = angle & 63;
	object->type = model;
}

void ParkingLot_Init(void)
{
	int coneModel;
	int barrierModel;
	int centerX;
	int centerZ;
	int x;
	int z;

	parkingLotObjectCount = 0;

	if (!gCustomParkingLot || PlayerStartInfo[0] == NULL)
		return;

	coneModel = FindModelIdxWithName("GREENCONE");
	barrierModel = FindModelIdxWithName("BARRIER_TASTIC");

	if (barrierModel < 0)
		barrierModel = FindModelIdxWithName("CRATE");

	centerX = PlayerStartInfo[0]->position.vx;
	centerZ = PlayerStartInfo[0]->position.vz;

	// A 12 x 8 metre practice box around the normal Chicago start surface.
	for (x = -6000; x <= 6000; x += 1500)
	{
		AddParkingLotObject(coneModel, centerX + x, 0, centerZ - 4000, 0);
		AddParkingLotObject(coneModel, centerX + x, 0, centerZ + 4000, 0);
	}

	for (z = -2500; z <= 2500; z += 1250)
	{
		AddParkingLotObject(coneModel, centerX - 6000, 0, centerZ + z, 0);
		AddParkingLotObject(coneModel, centerX + 6000, 0, centerZ + z, 0);
	}

	// Slalom and two solid end markers make the space immediately useful.
	for (z = -2250; z <= 2250; z += 1500)
		AddParkingLotObject(coneModel, centerX + ((z / 1500) & 1 ? 900 : -900), 0, centerZ + z, 0);

	AddParkingLotObject(barrierModel, centerX - 4500, 0, centerZ, 16);
	AddParkingLotObject(barrierModel, centerX + 4500, 0, centerZ, 16);
}

int ParkingLot_AppendDrawObjects(void** objects, int count, int capacity)
{
	int i;

	if (!gCustomParkingLot)
		return count;

	for (i = 0; i < parkingLotObjectCount && count < capacity; i++)
		objects[count++] = &parkingLotObjects[i];

	return count;
}

void ParkingLot_AppendEventObjects(CELL_OBJECT* objects, int* count, int capacity)
{
	int i;

	if (!gCustomParkingLot || objects == NULL)
		return;

	for (i = 0; i < parkingLotObjectCount && *count < capacity; i++)
		objects[(*count)++] = parkingLotObjects[i];
}
