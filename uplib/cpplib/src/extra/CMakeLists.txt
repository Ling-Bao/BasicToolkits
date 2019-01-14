set(FOLDER_NAME "extra")

CPPLIB_ADD_LIBRARY(extra
    location_optimizer.h location_optimizer.cc
    vp_detection.h vp_detection.cc)

set(LOCATION_OPTIMIZER_TEST location_optimizer_test.cc)
add_executable(location_optimizer_test
    ${LOCATION_OPTIMIZER_TEST}
    location_optimizer.cc)
target_link_libraries(location_optimizer_test PocoFoundation PocoJSON ${CPPLIB_LIBRARIES})

set(VP_DETECTION_TEST vp_detection_test.cc)
add_executable(vp_detection_test
    ${VP_DETECTION_TEST})
target_link_libraries(vp_detection_test ${CPPLIB_LIBRARIES})
