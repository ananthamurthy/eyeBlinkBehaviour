################################################################################
# ImageFormatControl_C Makefile
################################################################################

################################################################################
# Key paths and settings
################################################################################
CFLAGS += -std=c++11
CC = g++ ${CFLAGS}
OUTPUTNAME = ImageFormatControl_C${D}

OUTDIR = ../../bin

################################################################################
# Dependencies
################################################################################
# Spinnaker deps
SPINNAKER_LIB = -L../../lib -lSpinnaker${D} -lSpinnaker_C${D}

################################################################################
# Master inc/lib/obj/dep settings
################################################################################
OBJ = ImageFormatControl_C.o
INC = -I../../include/spinc
LIB += -Wl,-Bdynamic ${SPINNAKER_LIB} 
LIB += -Wl,-rpath-link=../../lib 

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
