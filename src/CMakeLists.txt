include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(ast ast.c)
add_library(datastructure datastructure.c)
add_library(Expression Expression.c)
add_library(Tokenizer Tokenizer.c)
add_library(parser parser.c)
add_library(hash hash.c)
add_library(variable variable.c)
add_library(interpreter interpreter.c)

target_link_libraries(ast PUBLIC datastructure)
target_link_libraries(Expression PUBLIC datastructure)
target_link_libraries(Expression  PUBLIC ast)


target_link_libraries(parser  PUBLIC datastructure)
target_link_libraries(parser  PUBLIC Tokenizer)
target_link_libraries(parser  PUBLIC Expression)
target_link_libraries(parser  PUBLIC ast)


target_link_libraries(variable  PUBLIC hash)

target_link_libraries(interpreter  PUBLIC variable)