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
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=remote
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/classes/ClientRequest.o \
	${OBJECTDIR}/classes/Currency.o \
	${OBJECTDIR}/classes/DB.o \
	${OBJECTDIR}/classes/HashTable.o \
	${OBJECTDIR}/classes/Market.o \
	${OBJECTDIR}/classes/Order.o \
	${OBJECTDIR}/classes/SocketServer.o \
	${OBJECTDIR}/classes/Thread.o \
	${OBJECTDIR}/classes/Transaction.o \
	${OBJECTDIR}/main.o


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
LDLIBSOPTIONS=-lpthread -lboost_filesystem-mt -lboost_program_options-mt -lboost_system-mt -lboost_thread-mt -lmongoclient

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bitcointradeengine

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bitcointradeengine: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bitcointradeengine ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/classes/ClientRequest.o: classes/ClientRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}/classes
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibraries/mongo/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/classes/ClientRequest.o classes/ClientRequest.cpp

${OBJECTDIR}/classes/Currency.o: classes/Currency.cpp 
	${MKDIR} -p ${OBJECTDIR}/classes
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibraries/mongo/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/classes/Currency.o classes/Currency.cpp

${OBJECTDIR}/classes/DB.o: classes/DB.cpp 
	${MKDIR} -p ${OBJECTDIR}/classes
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibraries/mongo/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/classes/DB.o classes/DB.cpp

${OBJECTDIR}/classes/HashTable.o: classes/HashTable.cpp 
	${MKDIR} -p ${OBJECTDIR}/classes
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibraries/mongo/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/classes/HashTable.o classes/HashTable.cpp

${OBJECTDIR}/classes/Market.o: classes/Market.cpp 
	${MKDIR} -p ${OBJECTDIR}/classes
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibraries/mongo/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/classes/Market.o classes/Market.cpp

${OBJECTDIR}/classes/Order.o: classes/Order.cpp 
	${MKDIR} -p ${OBJECTDIR}/classes
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibraries/mongo/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/classes/Order.o classes/Order.cpp

${OBJECTDIR}/classes/SocketServer.o: classes/SocketServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/classes
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibraries/mongo/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/classes/SocketServer.o classes/SocketServer.cpp

${OBJECTDIR}/classes/Thread.o: classes/Thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/classes
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibraries/mongo/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/classes/Thread.o classes/Thread.cpp

${OBJECTDIR}/classes/Transaction.o: classes/Transaction.cpp 
	${MKDIR} -p ${OBJECTDIR}/classes
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibraries/mongo/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/classes/Transaction.o classes/Transaction.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Ilibraries/mongo/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bitcointradeengine

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
