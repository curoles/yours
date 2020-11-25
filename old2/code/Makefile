include $(BASE)/code/TerminalAnsiColor.makefile

ECHO := echo

DITAA := /home/igor/tool/ditaa/ditaa
PYGMENTIZE := pygmentize -f html -O full,style=colorful,lineos=inline

SOURCE_DIR := $(BASE)/code/src
SCALA_SOURCES := $(shell find $(SOURCE_DIR)/main/scala -type f -name '*.scala')

BUILD_DIR := .

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

.PHONY: ditaa
ditaa: API_DIR := `pwd`/target/scala-2.10/api
ditaa: HTML_FILES := $(shell find $(API_DIR) -type f -name '*.html')
ditaa:
	@$(ECHO) $(call color-str,$(BIGre),Generate DITAA diagrams)
	@- $(foreach file,$(HTML_FILES), \
		cd $(dir $(file)) && $(DITAA) --html $(file) -o $(file) ; \
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
