  
  
namespace smart_home
{

inline Location::Location(FloorNumber a_floor, RoomNumber a_room)
: m_floor(a_floor)
, m_room(a_room) 
{}

inline Location::FloorNumber Location::floor() const {
    return m_floor; 
}

inline Location::RoomNumber Location::room() const { 
    return m_room; 
}


inline std::string Location::toString() const
{
    return m_floor + "^" + m_room;
}

} // namespace smart_home
