PROJECT_DIR=$(shell pwd)
#某些工程，可能里面存了有子目录，需要先编译子目录，然后再进行编译
MAKE_SUB_DIR=${PROJECT_DIR}

define MAKE_SUB_PROJECT
	@for subdir in $(MAKE_SUB_DIR); do \
		(echo "$$subdir" && cd $$subdir && make -f rm_makefile $1) \
	done
endef

ifndef CROSS_COMPILER
DEFINE_FILE=${PREFIX}/../sdk/defines
ifeq (${DEFINE_FILE}, $(wildcard ${DEFINE_FILE}))
include ${DEFINE_FILE}
endif
endif

.PHONY:all
all:
	$(call MAKE_SUB_PROJECT,CREATE_RELY_FILE)
	$(call MAKE_SUB_PROJECT,all)

.PHONY:install
install:
	$(call MAKE_SUB_PROJECT,CREATE_RELY_FILE)
	$(call MAKE_SUB_PROJECT,all)

.PHONY:clean
clean:
	$(call MAKE_SUB_PROJECT,clean)
