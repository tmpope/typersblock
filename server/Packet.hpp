//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2013 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//

#ifndef SFML_PACKET_HPP
#define SFML_PACKET_HPP

// Headers
#include <SFML/Network/Export.hpp>
#include <string>
#include <vector>


namespace sf
{
class String;
class TcpSocket;
class UdpSocket;

class SFML_NETWORK_API Packet
{
    // A bool-like type that cannot be converted to integer or pointer types
    typedef bool (Packet::*BoolType)(std::size_t);

public :

    Packet();

    virtual ~Packet();

    void append(const void* data, std::size_t sizeInBytes);

    void clear();

    const void* getData() const;

    std::size_t getDataSize() const;

    bool endOfPacket() const;

public:

    operator BoolType() const;

    Packet& operator >>(bool&         data);
    Packet& operator >>(Int8&         data);
    Packet& operator >>(Uint8&        data);
    Packet& operator >>(Int16&        data);
    Packet& operator >>(Uint16&       data);
    Packet& operator >>(Int32&        data);
    Packet& operator >>(Uint32&       data);
    Packet& operator >>(float&        data);
    Packet& operator >>(double&       data);
    Packet& operator >>(char*         data);
    Packet& operator >>(std::string&  data);
    Packet& operator >>(wchar_t*      data);
    Packet& operator >>(std::wstring& data);
    Packet& operator >>(String&       data);

    Packet& operator <<(bool                data);
    Packet& operator <<(Int8                data);
    Packet& operator <<(Uint8               data);
    Packet& operator <<(Int16               data);
    Packet& operator <<(Uint16              data);
    Packet& operator <<(Int32               data);
    Packet& operator <<(Uint32              data);
    Packet& operator <<(float               data);
    Packet& operator <<(double              data);
    Packet& operator <<(const char*         data);
    Packet& operator <<(const std::string&  data);
    Packet& operator <<(const wchar_t*      data);
    Packet& operator <<(const std::wstring& data);
    Packet& operator <<(const String&       data);

protected:

    friend class TcpSocket;
    friend class UdpSocket;

    virtual const void* onSend(std::size_t& size);

    virtual void onReceive(const void* data, std::size_t size);

private :

    bool operator ==(const Packet& right) const;
    bool operator !=(const Packet& right) const;

    bool checkSize(std::size_t size);

    // Member data
    std::vector<char> m_data;    
    std::size_t       m_readPos; 
    bool              m_isValid; 
};

} // namespace sf


#endif // SFML_PACKET_HPP