add_executable(TCP_demo ./test_Demo.c ./extern_libcurl.c ./extern_tools.c ./print.c)
#链接多线程库
target_link_libraries(pthread)

##############################################################
#查找curl库,如果没有找到就终止cmake的运行，找到了就链接库
FIND_PACKAGE(CURL)  
IF(CURL_FOUND)  
 INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR})  
 TARGET_LINK_LIBRARIES(TCP_demo ${CURL_LIBRARY})  
ELSE(CURL_FOUND)  
 MESSAGE(FATAL_ERROR "CURL library not found")  
ENDIF(CURL_FOUND)
##############################################################

#target_link_libraries(pthread)
#add_executable(mainStarter ./mainStarter/main.cc ./mainStarter/Starter.cc)
#target_link_libraries(mainStarter gdlp_base gdlp_adpters)
#install(TARGETS mainStarter  DESTINATION bin)

