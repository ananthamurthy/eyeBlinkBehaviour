################################################################################
# Acquisition Makefile
################################################################################

################################################################################
# Key paths and settings
################################################################################
CFLAGS += -std=c++11
CC = g++ ${CFLAGS}
OUTPUTNAME = Acquisition${D}
OUTDIR = ../../bin
OUTDIR = bin

################################################################################
# Dependencies
################################################################################
# Spinnaker deps
SPINNAKER_LIB = -L../../spinnaker_1_0_0_270_amd64/lib -lSpinnaker${D}

################################################################################
# Master inc/lib/obj/dep settings
################################################################################
OBJ = Acquisition.o
INC = -I../../spinnaker_1_0_0_270_amd64/include/
LIB += -Wl,-Bdynamic ${SPINNAKER_LIB} 
LIB += -Wl,-rpath-link=../../spinnaker_1_0_0_270_amd64/lib

################################################################################
# Rules/recipes
################################################################################
# Final binary
${OUTPUTNAME}: ${OBJ}
	${CC} -o ${OUTPUTNAME} ${OBJ} ${LIB}
	mv ${OUTPUTNAME} ${OUTDIR}

# Intermediate objects
%.o: %.cpp
	${CC} ${CFLAGS} ${INC} -Wall -c -D LINUX $*.cpp

# Clean up intermediate objects
clean_obj:
	rm -f ${OBJ}	@echo "all cleaned up!"

# Clean up everything.
clean:
	rm -f ${OUTDIR}/${OUTPUTNAME} ${OBJ}	@echo "all cleaned up!"
