#pragma once
bool GetDrop();
bool GetReMove();
bool GetErase();

void BlockInit();
void SearchLoadMap();
void Search_chengeMap();

void DrawMap(int c1,int c2);
void DarwMove(int x, float y, int c);
void DrawDrop();

void RandomBlock();

void DropSearch(); 
void DropSet(int x, int y);  
void DropMove();

void Search();
void Count(int x, int y);
void HitSet(int x, float y, int c);

void Deadcount();
void Des();