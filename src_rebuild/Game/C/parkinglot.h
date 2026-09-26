#ifndef PARKINGLOT_H
#define PARKINGLOT_H

extern int gCustomParkingLot;

extern void ParkingLot_Init(void);
extern int ParkingLot_AppendDrawObjects(void** objects, int count, int capacity);
extern void ParkingLot_AppendEventObjects(CELL_OBJECT* objects, int* count, int capacity);

#endif
