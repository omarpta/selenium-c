##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=selenium-c
ConfigurationName      :=Debug
WorkspacePath          :=/home/omar/data/omarpta/d/c/codelite-workspace
ProjectPath            :=/home/omar/github/selenium-c
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=omar
Date                   :=14/05/19
CodeLitePath           :=/home/omar/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/lib$(ProjectName).a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="selenium-c.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  $(shell pkg-config --libs libcurl glib-2.0)
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)include $(IncludeSwitch)submodules 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g $(Preprocessors)
CFLAGS   :=  -g -fPIC $(shell pkg-config --cflags libcurl glib-2.0) $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/submodules_sds_sds.c$(ObjectSuffix) $(IntermediateDirectory)/submodules_cJSON_cJSON_Utils.c$(ObjectSuffix) $(IntermediateDirectory)/submodules_cJSON_test.c$(ObjectSuffix) $(IntermediateDirectory)/submodules_cJSON_cJSON.c$(ObjectSuffix) $(IntermediateDirectory)/src_selenium.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList) $(ArLibs)
	@$(MakeDirCommand) "/home/omar/data/omarpta/d/c/codelite-workspace/.build-debug"
	@echo rebuilt > "/home/omar/data/omarpta/d/c/codelite-workspace/.build-debug/selenium-c"

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


./Debug:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/submodules_sds_sds.c$(ObjectSuffix): submodules/sds/sds.c $(IntermediateDirectory)/submodules_sds_sds.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/omar/github/selenium-c/submodules/sds/sds.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/submodules_sds_sds.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/submodules_sds_sds.c$(DependSuffix): submodules/sds/sds.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/submodules_sds_sds.c$(ObjectSuffix) -MF$(IntermediateDirectory)/submodules_sds_sds.c$(DependSuffix) -MM submodules/sds/sds.c

$(IntermediateDirectory)/submodules_sds_sds.c$(PreprocessSuffix): submodules/sds/sds.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/submodules_sds_sds.c$(PreprocessSuffix) submodules/sds/sds.c

$(IntermediateDirectory)/submodules_cJSON_cJSON_Utils.c$(ObjectSuffix): submodules/cJSON/cJSON_Utils.c $(IntermediateDirectory)/submodules_cJSON_cJSON_Utils.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/omar/github/selenium-c/submodules/cJSON/cJSON_Utils.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/submodules_cJSON_cJSON_Utils.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/submodules_cJSON_cJSON_Utils.c$(DependSuffix): submodules/cJSON/cJSON_Utils.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/submodules_cJSON_cJSON_Utils.c$(ObjectSuffix) -MF$(IntermediateDirectory)/submodules_cJSON_cJSON_Utils.c$(DependSuffix) -MM submodules/cJSON/cJSON_Utils.c

$(IntermediateDirectory)/submodules_cJSON_cJSON_Utils.c$(PreprocessSuffix): submodules/cJSON/cJSON_Utils.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/submodules_cJSON_cJSON_Utils.c$(PreprocessSuffix) submodules/cJSON/cJSON_Utils.c

$(IntermediateDirectory)/submodules_cJSON_test.c$(ObjectSuffix): submodules/cJSON/test.c $(IntermediateDirectory)/submodules_cJSON_test.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/omar/github/selenium-c/submodules/cJSON/test.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/submodules_cJSON_test.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/submodules_cJSON_test.c$(DependSuffix): submodules/cJSON/test.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/submodules_cJSON_test.c$(ObjectSuffix) -MF$(IntermediateDirectory)/submodules_cJSON_test.c$(DependSuffix) -MM submodules/cJSON/test.c

$(IntermediateDirectory)/submodules_cJSON_test.c$(PreprocessSuffix): submodules/cJSON/test.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/submodules_cJSON_test.c$(PreprocessSuffix) submodules/cJSON/test.c

$(IntermediateDirectory)/submodules_cJSON_cJSON.c$(ObjectSuffix): submodules/cJSON/cJSON.c $(IntermediateDirectory)/submodules_cJSON_cJSON.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/omar/github/selenium-c/submodules/cJSON/cJSON.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/submodules_cJSON_cJSON.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/submodules_cJSON_cJSON.c$(DependSuffix): submodules/cJSON/cJSON.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/submodules_cJSON_cJSON.c$(ObjectSuffix) -MF$(IntermediateDirectory)/submodules_cJSON_cJSON.c$(DependSuffix) -MM submodules/cJSON/cJSON.c

$(IntermediateDirectory)/submodules_cJSON_cJSON.c$(PreprocessSuffix): submodules/cJSON/cJSON.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/submodules_cJSON_cJSON.c$(PreprocessSuffix) submodules/cJSON/cJSON.c

$(IntermediateDirectory)/src_selenium.c$(ObjectSuffix): src/selenium.c $(IntermediateDirectory)/src_selenium.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/omar/github/selenium-c/src/selenium.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_selenium.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_selenium.c$(DependSuffix): src/selenium.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_selenium.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_selenium.c$(DependSuffix) -MM src/selenium.c

$(IntermediateDirectory)/src_selenium.c$(PreprocessSuffix): src/selenium.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_selenium.c$(PreprocessSuffix) src/selenium.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


