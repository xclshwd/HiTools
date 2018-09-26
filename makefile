PROJECT_DIR=$(shell pwd)
#某些工程，可能里面存了有子目录，需要先编译子目录，然后再进行编译
#MAKE_SUB_DIR+=${PROJECT_DIR}/include
#MAKE_SUB_DIR+=${PROJECT_DIR}/sdk
#MAKE_SUB_DIR+=${PROJECT_DIR}/opensource
MAKE_SUB_DIR+=${PROJECT_DIR}/RMH264ToMP4
#MAKE_SUB_DIR+=${PROJECT_DIR}/libtoolkit
#MAKE_SUB_DIR+=${PROJECT_DIR}/librmfs
#MAKE_SUB_DIR+=${PROJECT_DIR}/libcommon
#MAKE_SUB_DIR+=${PROJECT_DIR}/webservice
#MAKE_SUB_DIR+=${PROJECT_DIR}/storage
#MAKE_SUB_DIR+=${PROJECT_DIR}/devicemanage
#MAKE_SUB_DIR+=${PROJECT_DIR}/parameter
#MAKE_SUB_DIR+=${PROJECT_DIR}/guiprocess
#MAKE_SUB_DIR+=${PROJECT_DIR}/networkprotocol
#MAKE_SUB_DIR+=${PROJECT_DIR}/networkservice
#MAKE_SUB_DIR+=${PROJECT_DIR}/basicservice
#MAKE_SUB_DIR+=${PROJECT_DIR}/smalltools
#MAKE_SUB_DIR+=${PROJECT_DIR}/smallsystem
#MAKE_SUB_DIR+=${PROJECT_DIR}/resources

define MAKE_SUB_PROJECT
	@for subdir in $(MAKE_SUB_DIR); do \
		cd $$subdir; \
		mkdir -p ${RELEASE_ROOT_DIR}/$$(basename $$subdir); \
		make $1 NO_DEFINES=y PREFIX=${RELEASE_ROOT_DIR}/$$(basename $$subdir); \
	done
endef

ifndef NO_DEFINES
-include ./defines
endif

.PHONY:all
all:
	$(call MAKE_SUB_PROJECT,all)

.PHONY:install
install:
	$(call MAKE_SUB_PROJECT,all)

.PHONY:clean
clean:
	$(call MAKE_SUB_PROJECT,clean)
