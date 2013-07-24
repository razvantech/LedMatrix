/*
  LedMatrix.h - Library for controlling 8*8 LED matrix through SPI
	Created by Razvan Chiriac, July 18th, 2013
*/
// Connect to "Output SPI" JP4 on LED Matrix
// DIO 10 = CSn  (JP4-3)
// DIO 11 = MOSI (JP4-2)
// DIO 13 = SCK  (JP4-4)
//     5V = VCC  (JP4-5 or JP4-6)
//    GND = GND  (JP4-1)

#ifndef LedMatrix_h
#define LedMatrix_h

#include "Arduino.h"
#include "SPI.h"



class LedMatrix {
	public:
		LedMatrix(int CSn);
		
		void make();
		void setMatrix(int color);
		void drawSquare(int x, int y, int side, int color);
		void drawDot(int x, int y, int color);
		void drawDotOver(int x, int y, int color);
		void clearDotOver(int x, int y);
		
		int matrix [8][8];
	private:
		int _CSn;
		
		
};

#endif
