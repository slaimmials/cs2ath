#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

template< typename T >
std::string int_to_hex(T i);
float i32tf(uint32_t f);

void WriteInt(uintptr_t Address, int Value);
void WriteFloat(uintptr_t Address, float Value);
void WriteDouble(uintptr_t Address, double Value);
void WriteBool(uintptr_t Address, bool Value);

int ReadInt(uintptr_t Address);
float ReadFloat(uintptr_t Address);
double ReadDouble(uintptr_t Address);
bool ReadBool(uintptr_t Address);

uintptr_t GetPointer(HMODULE Module, int Address, std::vector<int> Offsets);
uintptr_t GetPointer(uintptr_t Address, int Offset);