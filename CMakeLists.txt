cmake_minimum_required(VERSION 3.19)
project(webserver)

set(CMAKE_CXX_STANDARD 98)

add_executable(webserver2
        main.cpp
        server/RequestHandler.cpp
        server/ServerManager.cpp
        server/Socket.cpp
        parser/ConfigParser.cpp
        parser/GetServer.cpp
        parser/Route.cpp
        parser/ServerConfig.cpp
        parser/utils.cpp
        http/Content/AContent.cpp
        http/Content/ContentFile.cpp
        http/Content/ContentSocket.cpp
        http/Connect.cpp
        http/Connections.cpp
        http/Request.cpp
        http/RequestData.cpp
        http/Responce.cpp
        cgi/HandlerCGI.cpp)