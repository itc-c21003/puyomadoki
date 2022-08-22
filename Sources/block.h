#pragma once
bool GetDrop();
bool GetReMove();

void BlockInit();
void SearchLoadMap();
void Search_chengeMap();
void DrawBlock(int x1, int x2, float y1, float y2, int c1, int c2);
void RandomBlock();

void DropSearch(); 
void DropSet(int x, int y);  
void DropMove();

void Search();
void Count(int x, int y, int n);
void HitSet(int x, float y, int c);