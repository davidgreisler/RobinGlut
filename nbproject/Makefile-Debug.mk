#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=LC_ALL=C g++
CXX=LC_ALL=C g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/robinglut/user_interface.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/robinglut/scene.o \
	${OBJECTDIR}/src/robinglut/glut_renderer.o \
	${OBJECTDIR}/src/robinglut/menu.o \
	${OBJECTDIR}/src/robinglut/level.o \
	${OBJECTDIR}/src/robinglut/robin_glut.o \
	${OBJECTDIR}/src/robinglut/game.o \
	${OBJECTDIR}/pfeil.o \
	${OBJECTDIR}/src/robinglut/raw_loader.o \
	${OBJECTDIR}/src/robinglut/bow.o \
	${OBJECTDIR}/src/robinglut/arrow.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lGLU -lglut

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robinglut

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robinglut: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robinglut ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/robinglut/user_interface.o: src/robinglut/user_interface.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/robinglut
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/robinglut/user_interface.o src/robinglut/user_interface.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/robinglut/scene.o: src/robinglut/scene.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/robinglut
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/robinglut/scene.o src/robinglut/scene.cpp

${OBJECTDIR}/src/robinglut/glut_renderer.o: src/robinglut/glut_renderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/robinglut
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/robinglut/glut_renderer.o src/robinglut/glut_renderer.cpp

${OBJECTDIR}/src/robinglut/menu.o: src/robinglut/menu.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/robinglut
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/robinglut/menu.o src/robinglut/menu.cpp

${OBJECTDIR}/src/robinglut/level.o: src/robinglut/level.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/robinglut
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/robinglut/level.o src/robinglut/level.cpp

${OBJECTDIR}/src/robinglut/robin_glut.o: src/robinglut/robin_glut.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/robinglut
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/robinglut/robin_glut.o src/robinglut/robin_glut.cpp

${OBJECTDIR}/src/robinglut/game.o: src/robinglut/game.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/robinglut
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/robinglut/game.o src/robinglut/game.cpp

${OBJECTDIR}/pfeil.o: pfeil.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/pfeil.o pfeil.cpp

${OBJECTDIR}/src/robinglut/raw_loader.o: src/robinglut/raw_loader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/robinglut
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/robinglut/raw_loader.o src/robinglut/raw_loader.cpp

${OBJECTDIR}/src/robinglut/bow.o: src/robinglut/bow.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/robinglut
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/robinglut/bow.o src/robinglut/bow.cpp

${OBJECTDIR}/src/robinglut/arrow.o: src/robinglut/arrow.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/robinglut
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/robinglut/arrow.o src/robinglut/arrow.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robinglut

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc