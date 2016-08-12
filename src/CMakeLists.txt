set(LIB_SOURCES
  roman_numeral_calculator.c
)

set(MAIN_SOURCES
  main.c
)

set(HEADERS
  ${CONFIG_HEADER}
  roman_numeral_calculator.h
)

add_library(roman_numeral_calculator STATIC ${LIB_SOURCES} ${HEADERS})

add_executable(main ${HEADERS} ${MAIN_SOURCES})
target_link_libraries(main roman_numeral_calculator)

install(TARGETS roman_numeral_calculator
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/roman_numeral_calculator.h DESTINATION include)
