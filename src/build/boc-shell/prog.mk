NAME:=boc-shell
BIN_DIR:=$(BUILD_BIN)

DEPENDENCIES:= \
	libs/system \
	libs/program \
	libs/text \
	libs/ast \
	libs/system \
	build/boc-shell/sexpr \

SOURCES:= \
	argument_visitor.cpp \
	assignment_visitor.cpp \
	ast.cpp \
	builtins.cpp \
	expression_visitor.cpp \
	io_redirection_visitor.cpp \
	lexer.cpp \
	main.cpp \
	parser.cpp \
	program_visitor.cpp \
	stack.cpp \
	symbols.cpp \
	symbol_visitor.cpp \
	word_visitor.cpp \

LIBRARIES:=$(SYSTEM_LIBRARIES)
