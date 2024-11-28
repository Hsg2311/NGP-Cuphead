#include <iostream>
#include <unordered_map>
#include <queue>

#include "Object.hpp"


std::unordered_map<int, Object*> networkIDToObject;
PacketQueue packetQueue;