  
  
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

inline bool Location::equal(Location const& a_other) const
{
    return m_floor == a_other.m_floor && m_room == a_other.m_room;
}
inline bool operator==(Location const& a_lop, Location const& a_rop)
{
    return a_lop.equal(a_rop);
}



} // namespace smart_home
