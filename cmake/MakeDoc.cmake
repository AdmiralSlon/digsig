# -------------------------------------------------------------------------------------------------- #
# Copyright (c) 2014 - 2022 by Axel Kenzo, axelkenzo@mail.ru
#
# MakeDoc.cmake
# -------------------------------------------------------------------------------------------------- #
find_program( GZIP gzip )
if( GZIP )
  message( "-- gzip found (${GZIP})" )
else()
  message( "-- gzip not found" )
endif()

find_program( SPHINX sphinx-build )
if( SPHINX )
  message( "-- sphinx-build found (${SPHINX})" )
else()
  message( "-- sphinx-build not found" )
endif()

find_program( DOXYGEN doxygen )
if( DOXYGEN )
  message( "-- doxygen found (${DOXYGEN})" )
else()
  message( "-- doxygen not found" )
endif()

find_program( LATEXMK latexmk )
if( LATEXMK )
  message( "-- latexmk found (${LATEXMK})" )
else()
  message( "-- latexmk not found" )
endif()

find_program( QHELPGENERATOR qhelpgenerator )
if( QHELPGENERATOR )
  message( "-- qhelpgenerator found (${QHELPGENERATOR})" )
else()
  message( "-- qhelpgenerator not found" )
endif()

# -------------------------------------------------------------------------------------------------- #
if( DOXYGEN )
  # doxygen найден и документация может быть сгенерирована
  # configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY )
endif()

# -------------------------------------------------------------------------------------------------- #
if( UNIX )
  if( SPHINX )
    configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/doc/Makefile.in ${CMAKE_CURRENT_BINARY_DIR}/sphinx/Makefile @ONLY )

    set( script ${CMAKE_CURRENT_BINARY_DIR}/make-doc-${FULL_VERSION}.sh )
    file( WRITE ${script} "#/bin/bash\n cd ${CMAKE_CURRENT_BINARY_DIR}/sphinx \n" )
   # формируем каталог с собранной воедино документацией
    file( APPEND ${script} "mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/doc\n" )
   # строим красивый вывод в html
    file( APPEND ${script} "make html\n" )
    file( APPEND ${script} "tar -cjvf ${CMAKE_CURRENT_BINARY_DIR}/doc/libakrypt-doc-${FULL_VERSION}.tar.bz2 html/* \n" )
   # формируем консольный мануал (в сжатом виде)
   # и сохраняем изначальный (несжатый) man в дереве исходных кодов
    file( APPEND ${script} "make man\n" )
    file( APPEND ${script} "cp ${CMAKE_CURRENT_BINARY_DIR}/sphinx/man/aktool.1 ${CMAKE_CURRENT_SOURCE_DIR}/aktool \n" )
    file( APPEND ${script} "cp ${CMAKE_CURRENT_BINARY_DIR}/sphinx/man/aktool.1 ${CMAKE_CURRENT_BINARY_DIR}/doc/aktool.1 \n" )
    if( GZIP )
      file( APPEND ${script} "gzip --force ${CMAKE_CURRENT_BINARY_DIR}/doc/aktool.1 \n" )
    endif()
   # формируем документацию в формате qthelp
    if( QHELPGENERATOR )
      file( APPEND ${script} "make qthelp\n" )
      file( APPEND ${script} "qcollectiongenerator qthelp/libakrypt.qhcp\n" )
      file( APPEND ${script} "cp ${CMAKE_CURRENT_BINARY_DIR}/sphinx/qthelp/libakrypt.qch ${CMAKE_CURRENT_BINARY_DIR}/doc/libakrypt-doc-${FULL_VERSION}.qch\n" )
    endif()
   # формируем документацию в формате pdf
    if( LATEXMK )
      file( APPEND ${script} "make latexpdf\n" )
      file( APPEND ${script} "cp ${CMAKE_CURRENT_BINARY_DIR}/sphinx/latex/libakrypt.pdf ${CMAKE_CURRENT_BINARY_DIR}/doc/libakrypt-doc-${FULL_VERSION}.pdf\n" )
    endif()
    file( APPEND ${script} "cd ${CMAKE_CURRENT_BINARY_DIR}\n" )
   # добавляем цель сборки
    execute_process( COMMAND chmod +x ${script} )
    add_custom_target( doc ${script} )
    message("-- Script for documentation is done (now \"make doc\" enabled)")

  endif()
endif()
# -------------------------------------------------------------------------------------------------- #
#                                                                                     MakeDoc.cmake  #
# -------------------------------------------------------------------------------------------------- #


