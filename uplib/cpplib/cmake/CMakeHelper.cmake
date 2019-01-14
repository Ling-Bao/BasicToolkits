# Macro used to define that all following targets should be treated as
# 3rd-party targets.
macro(CPPLIB_SET_THIRD_PARTY_FOLDER)
    set(CPPLIB_THIRD_PARTY_FOLDER TRUE)
endmacro(CPPLIB_SET_THIRD_PARTY_FOLDER)

# Macro used to define that all following targets should not be treated as
# 3rd-party targets.
macro(CPPLIB_UNSET_THIRD_PARTY_FOLDER)
    set(CPPLIB_THIRD_PARTY_FOLDER FALSE)
endmacro(CPPLIB_UNSET_THIRD_PARTY_FOLDER)

# Replacement for the normal add_library() command. The syntax remains the same
# in that the first argument is the target name, and the following arguments
# are the source files to use when building the target.
macro(CPPLIB_ADD_LIBRARY TARGET_NAME)
    # ${ARGN} will store the list of source files passed to this function.
    add_library(${TARGET_NAME} ${ARGN})
endmacro(CPPLIB_ADD_LIBRARY)