cmake_minimum_required(VERSION 3.27)
project(Matam_HW4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Events)
include_directories(Players)

add_executable(Matam_HW4
        Events/Encounter.cpp
        Events/Encounter.h
        Events/Event.cpp
        Events/Event.h
        Events/SpecialEvent.cpp
        Events/SpecialEvent.h
        Players/Character.cpp
        Players/Character.h
        Players/Job.cpp
        Players/Job.h
        Players/Player.cpp
        Players/Player.h
        main.cpp
        Utilities.cpp
        Utilities.h
        Players/PlayersFactory.cpp
        Players/PlayersFactory.cpp
        Players/PlayersFactory.cpp
        MatamStory.cpp)
