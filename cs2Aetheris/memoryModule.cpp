#include "MemoryModule.h"
#include <iostream>
using namespace std;

template< typename T >
std::string int_to_hex(T i)
{
    std::stringstream stream;
    stream << std::hex << i;
    std::string result(stream.str());
    return result;
}

float i32tf(uint32_t f)
{
    return std::_Bit_cast<float>(f);
}

//WRITES
void WriteInt(uintptr_t Address, int Value) {
    *reinterpret_cast<int*>(Address) = Value;
    std::cout << int_to_hex(Address) << " => (int) " << Value << std::endl;
}
void WriteFloat(uintptr_t Address, float Value) {
    *reinterpret_cast<float*>(Address) = Value;
    std::cout << int_to_hex(Address) << " => (float) " << Value << std::endl;
}
void WriteDouble(uintptr_t Address, double Value) {
    *reinterpret_cast<double*>(Address) = Value;
    std::cout << int_to_hex(Address) << " => (double) " << Value << std::endl;
}
void WriteBool(uintptr_t Address, bool Value) {
    *reinterpret_cast<bool*>(Address) = Value;
    std::cout << int_to_hex(Address) << " => (bool) " << std::boolalpha << Value << std::endl;
}

//READS
int ReadInt(uintptr_t Address) {
	return *reinterpret_cast<int*>(Address);
}
float ReadFloat(uintptr_t Address) {
    return *reinterpret_cast<float*>(Address);
}
double ReadDouble(uintptr_t Address) {
    return *reinterpret_cast<double*>(Address);
}
bool ReadBool(uintptr_t Address) {
    return *reinterpret_cast<bool*>(Address);
}

//Pointer manipulations
uintptr_t GetPointer(HMODULE Module, int Address, vector<int> Offsets) {
    uintptr_t base = (uintptr_t)Module;
    uintptr_t firstPass = base + Address;
    uintptr_t endPass;
    for (int i = 0; i < Offsets.size(); ++i) {
        firstPass = *(uintptr_t*)firstPass + Offsets[i];
    }
    return firstPass;
}

uintptr_t GetPointer(uintptr_t Address, int Offset) {
    uintptr_t firstPass = *(uintptr_t*)Address + Offset;
    return firstPass;
}