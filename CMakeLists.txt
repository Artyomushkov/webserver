cmake_minimum_required(VERSION 3.19)
project(webserver)

set(CMAKE_CXX_STANDARD 98)

add_executable(webserver main.cpp server/ServerManager.cpp server/RequestHandler.cpp server/Socket.cpp
        parser/ServerConfig.cpp parser/utils.cpp parser/Route.cpp
        parser/ConfigParser.cpp
        http/Msimon/Content/AContent.cpp
        http/Msimon/Content/ContentSocket.cpp http//Msimon/Content/ContentFile.cpp
        http/Msimon/Connections.cpp http/Msimon/Request.cpp
        http/Msimon/RequestData.cpp http/Msimon/Responce.cpp)