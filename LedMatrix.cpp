/*
  LedMatrix.cpp - Library for controlling 8*8 LED matrix through SPI
	Uses the SPI library for SPI communication
	Created by Razvan Chiriac, July 18th, 2013
	Connect to "Output SPI" JP4 on LED Matrix
	DIO 10 = CSn  (JP4-3)
	DIO 11 = MOSI (JP4-2)
	DIO 13 = SCK  (JP4-4)
		5V = VCC  (JP4-5 or JP4-6)
	   GND = GND  (JP4-1)
*/

#include "Arduino.h"
#include "LedMatrix.h"
#include "SPI.h"


//constructor
LedMatrix::LedMatrix(int CSn)
{
	pinMode(CSn, OUTPUT);
	_CSn = CSn;
	
	SPI.begin();
	SPI.setClockDivider(SPI_CLOCK_DIV128);
	SPI.setDataMode(SPI_MODE0);
}

//make() transfers values from the 2D array called matrix[][]
//to the led matrix through SPI
//gets called after matrix[][] is set as desired
void LedMatrix::make()
{
  digitalWrite(_CSn,LOW);
  delay(1);
  for ( int i=0; i<8; i++ )
    {
      for ( int j=0; j<8; j++ )
      {
        SPI.transfer(matrix[i][j]);
      }
    }
  delay(1);
  digitalWrite(_CSn,HIGH);
}

//setMatrix(int color) makes matrix[][] to one value
//1=green. 2=red. 3=yellow.
void LedMatrix::setMatrix(int color)
{
    for(int r=0;r<8;r++){
    for(int c=0;c<8;c++){
      matrix[r][c]= color;
    }
  }
}

//drawSquare(int x, int y, int side, int color) draws a square
//x, y = upper-right corner coordinates (1-8).
//side = side length. color: 1=green. 2=red. 3=yellow.
void LedMatrix::drawSquare(int x, int y, int side, int color)
{
	int row = (y-1)%8;
  	int col = (x-1)%8;
    setMatrix(0);
  	make();
  	for (int s=0; s<side; s++){
    	matrix[row][col+s]=color;
    	matrix[row+s][col]=color;
    	matrix[row+side-1][col+s]=color;
    	matrix[row+s][col+side-1]=color;
  	}
  
  	make();
  	setMatrix(0);
}

//drawDot(int x, int y, int color) draws one dot
//x, y = coordinates (1-8).
//color: 1=green. 2=red. 3=yellow.
void LedMatrix::drawDot(int x, int y, int color)
{
  	setMatrix(0);
  	matrix[y-1][x-1] = color;
  	make();
  	setMatrix(0);
}

//drawDotOver(int x, int y, int color) draws 
//one dor without erasing what was on the screen before
//x, y = coordinates (1-8).
//color: 1=green. 2=red. 3=yellow.
void LedMatrix::drawDotOver(int x, int y, int color)
{
  	matrix[y-1][x-1] = color;
  	make();
}

//clearDotOver(int x, int y) erases the dot
//at coordinates x and y (1-8)
void LedMatrix::clearDotOver(int x, int y)
{
  	matrix[y-1][x-1] = 0;
  	make();
}
