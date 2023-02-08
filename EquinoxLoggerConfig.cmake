add_library(EquinoxLogger SHARED IMPORTED)
find_library(EQUINOX_LOGGER_LIBRARY_PATH EquinoxLogger HINTS "${CMAKE_CURRENT_LIST_DIR}/../../")
set_target_properties(EquinoxLogger PROPERTIES IMPORTED_LOCATION "${EQUINOX_LOGGER_LIBRARY_PATH}")