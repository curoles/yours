include $(BASE)/code/TerminalAnsiColor.makefile

ECHO := echo

DITAA := /home/igor/tool/ditaa/ditaa
PYGMENTIZE := pygmentize -f html -O full,style=colorful,lineos=inline

SOURCE_DIR := $(BASE)/code/src
SCALA_SOURCES := $(shell find $(SOURCE_DIR)/main/scala -type f -name '*.scala')

BUILD_DIR := .
DOC_DIR := $(BUILD_DIR)/doc
HTML_SRC := $(DOC_DIR)/htmlsrc

.PHONY: compile
compile:
	sbt -v compile

.PHONY: run
run:
	sbt -v run

.PHONY: doc
doc:
	@$(ECHO) $(call color-str,$(BIGre),Make documentation)
	sbt doc

.PHONY: clean
clean:
	sbt clean

.PHONY: htmlsrc
htmlsrc: API_DIR := $(BUILD_DIR)/target/scala-2.10/api
htmlsrc:
	@$(ECHO) $(call color-str,$(BIGre),Make Scala source files html representation)
	@- $(foreach srcfile,$(SCALA_SOURCES), \
		$(eval outfile = $(API_DIR)/$(subst $(SOURCE_DIR)/main/scala/,,$(srcfile)).html) \
		mkdir -p $(dir $(outfile)) ; \
		$(PYGMENTIZE) -l scala -o $(outfile) $(srcfile) ; \
	)


#cd $(@D) && $(DITAA) --html $< -o $@.diag 

#SRC_DIR := ../yours/v2
#SRC := $(SRC_DIR)/Yours.scala $(SRC_DIR)/yours/SentenceParser.scala
#
#compile:
#	scalac -d classes $(SRC)
#
#run:
#	scala -cp classes Yours
