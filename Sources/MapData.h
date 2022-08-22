#pragma once
const int MAP_X = 8, MAP_Y = 13, MapMax = MAP_X * MAP_Y ,CHIPSIZE = 32;
void ResetMap(); 
int Map_GetData(int i);
void Chenge_MapData(int i, int c);