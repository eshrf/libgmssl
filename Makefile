SM2OBJ=sm2_lib.o sm2_asn1.o sm2_err.o sm2_sign.o sm2_enc.o sm2_kap.o kdf_x9_63.o
SM3OBJ=sm3.o m_sm3.o
SM4OBJ=sms4_cbc.o sms4_cfb.o sms4_ecb.o sms4_ofb.o sms4_ctr.o sms4_wrap.o sms4.o e_sms4.o
TEST=gm sm2 sm4
ALL=libgmssl.so $(TEST)

LOCAL_OPENSSL_INC=$(SSL_ROOT)/include
LOCAL_OPENSSL_LIB=$(SSL_ROOT)/lib

CFLAGS=-g -O2 -fPIC -Wall -I$(LOCAL_OPENSSL_INC)

all: $(ALL)


test:gm sm2 sm4
	LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH ./gm
	LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH ./sm2
	LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH ./sm4

gm: gmtest.o libgmssl.so
	gcc -o $@ $< -L$(LOCAL_OPENSSL_LIB) -lcrypto -ldl -L. -lgmssl -lcrypto

sm4: sms4test.o libgmssl.so
	gcc -o $@ $< -L$(LOCAL_OPENSSL_LIB) -lcrypto -ldl -L. -lgmssl -lcrypto

sm2: sm2test.o libgmssl.so
	gcc -o $@ $< -L$(LOCAL_OPENSSL_LIB) -lcrypto -ldl -L. -lgmssl -lcrypto

libgmssl.so: $(SM2OBJ) $(SM3OBJ) $(SM4OBJ)
	gcc -o $@ $+ -fPIC -shared -L$(LOCAL_OPENSSL_LIB) -lcrypto

libgmssl.a: $(SM2OBJ) $(SM3OBJ) $(SM4OBJ)
	ar rcu $@ $+

clean:
	rm -rf $(ALL) *.o

INSTALL_TOP=/usr/local
install: libgmssl.a
	mkdir -p $(INSTALL_TOP)/include $(INSTALL_TOP)/lib
	cp *.h $(INSTALL_TOP)/include
	cp libgmssl.a $(INSTALL_TOP)/lib
