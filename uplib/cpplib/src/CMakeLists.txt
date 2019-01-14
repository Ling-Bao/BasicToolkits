include_directories(
        .
        ${Boost_INCLUDE_DIRS}
        ${EIGEN3_INCLUDE_DIRS}
        ${CERES_INCLUDE_DIRS}
        ${GLUT_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
        ${Qt5_INCLUDE_DIRS}
)

link_directories(
        ${Boost_LIBRARY_DIRS}
)

set(CPPLIB_LIBRARIES
        lsd
        extra
        util
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_REGEX_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${CERES_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${OpenCV_LIBRARIES})

add_subdirectory(ext)
add_subdirectory(extra)
add_subdirectory(util)

# Prevent the library from being compiled automatically.
set_target_properties(
        ${CPPLIB_SRC_ROOT_FOLDER} PROPERTIES
        EXCLUDE_FROM_ALL 1
        EXCLUDE_FROM_DEFAULT_BUILD 1)