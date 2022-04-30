CC=gcc
CFLAGS=-Wall -Wextra -Wno-unknown-pragmas 
DFLAGS=-DMG_ENABLE_SSL -DMG_ENABLE_OPENSSL=1 lib/libmongoose/mongoose.c lib/BSD/strsec.c  
HARDENING= -fstack-protector-all -pie -fPIE -ftrapv
DIR=src/
DIROUT=bin/
DIR_HEADERS=src/headers/
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
 LDFLAGS=-lpthread -lcrypto -lssl -lm 
else
 LDFLAGS=-Wl,-z,relro,-z,now -lpthread -lm -lcrypto -lssl
endif

optionscat: $(DIR)rest_server.c 
	@echo "Compile... "
	$(CC) $(CFLAGS) $(DFLAGS) -c $(DIR)*.c -I$(DIR_HEADERS) -Ilib
	$(CC) -o $(DIROUT)rest_server *.o $(LDFLAGS) $(HARDENING)
	$(shell make clean)
	@echo "  "
	@echo " Next step, execute \"bin/rest_server\" to start...  "   
clean:
	rm -f *.o rest_server
