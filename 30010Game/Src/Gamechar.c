#include "Gamechar.h"

const char game_char_data[][5] = {
		{0x00, 0x00, 0x00, 0x00, 0x00}, //0 Clear
		{0xBE, 0xFF, 0xF3, 0xBE, 0x00}, //1  Bullet
		{0x0E, 0x1F, 0x3F, 0x7F, 0xFE}, //2  Heart 1
		{0xFE, 0x7B, 0x31, 0x1B, 0x0E}, //3  Heart 2
		{0x1E, 0x0E, 0x0E, 0x12, 0x20}, //4  Arrow up-left
		{0x08, 0x0C, 0x3E, 0x0C, 0x08}, //5  Arrow up
		{0x20, 0x12, 0x0E, 0x0E, 0x1E}, //6  Arrow up-right
		{0x00, 0x80, 0xC0, 0x00, 0x00}, //7  Arrow left1
		{0x01, 0x03, 0x07, 0x01, 0x01}, //8  Arrow left2
		{0x00, 0x00, 0xC0, 0x80, 0x00}, //9  Arrow right1
		{0x01, 0x01, 0x07, 0x03, 0x01}, //10 Arrow right2
		{0xF0, 0xE0, 0xE0, 0x90, 0x08}, //11 Arrow down-left
		{0x20, 0x60, 0xF9, 0x60, 0x20}, //12 Arrow down
		{0x08, 0x90, 0xE0, 0xE0, 0xF0}, //13 Arrow down-right
		{0xFE, 0x12, 0x12, 0x12, 0xEC}, //14 R
		{0x40, 0xA8, 0xA8, 0xA8, 0xF0}, //15 a
		{0x70, 0x88, 0x88, 0x90, 0xFE}, //16 d
		{0x40, 0xA8, 0xA8, 0xA8, 0xF0}, //17 a
		{0xF8, 0x10, 0x08, 0x08, 0x10}, //18 r
		{0xFE, 0x92, 0x92, 0x92, 0x82}, //19 E
		{0xF8, 0x10, 0x08, 0x08, 0xF0}, //20 n
		{0x70, 0xA8, 0xA8, 0xA8, 0x30}, //21 e
		{0xF8, 0x08, 0x30, 0x08, 0xF0}, //22 m
		{0x18, 0xA0, 0xA0, 0xA0, 0x78}, //23 y
		{0xFF, 0x55, 0x11, 0x01, 0x00}, //24 Full[1]/dotted[2-5] lines
		{0x00, 0x00, 0x00, 0x00, 0x00}};
