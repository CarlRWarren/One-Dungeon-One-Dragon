#include "id.h"

size_t ID::ms_uniqueID = 0;

ID::ID() {
	m_id = GetUniqueID();
}

std::string ID::GetUniqueID() {
	return "uID" + std::to_string(ms_uniqueID++);
}