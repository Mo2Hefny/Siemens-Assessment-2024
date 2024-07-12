set(This Packet)

project(${This} C CXX)

set(Headers
    packet.h
)

set(Sources
    main.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})