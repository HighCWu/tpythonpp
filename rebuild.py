#!/usr/bin/python
import os, sys, subprocess

## Ubuntu Notes:
## sudo apt-get install g++-arm-linux-gnueabi gcc-arm-linux-gnueabi binutils-arm-linux-gnueabi


Makefile = '''
## note this Makefile is autogenerated by rebuild.py ##

TINYPYC=./tpc

#RUNTIME_FILES=types.py testing.py
RUNTIME_FILES=types.py
RUNTIME_C_FILES=$(RUNTIME_FILES:%.py=tinypy/runtime/%.cpp)

## note: the self-hosted compiler is DEPRECATED,
## bytecode is generated by the classic python compiler.
#COMPILER_FILES=boot.py encode.py parse.py py2bc.py tokenize.py
#COMPILER_C_FILES=$(COMPILER_FILES:%.py=tinypy/compiler/%.cpp)


VMLIB_FILES=tp.cpp dummy-compiler.cpp runtime.cpp
TPLIB_FILES=tp.cpp compiler.cpp runtime.cpp

#MODULES=math random re
#MODULES_A_FILES=$(MODULES:%=modules/%.a)
#MODULES_C_FILES=$(MODULES:%=modules/%/init.cpp)

%.cpp : %.py
	$(TINYPYC) -co $@ $^


%.o : %.cpp
	<CC> $(CFLAGS) <DEFINES> -std=c++11 -g -rdynamic -O2 -I/usr/local/include/python3.7m -I . -c -o $@ $<
#	c++ $(CFLAGS) -DDEBUG=1 -std=c++11 -g -rdynamic -O0 -I/usr/local/include/python3.7m -I . -c -o $@ $<

all: <EXE>

#modules/modules.c: $(MAKEFILE)
#	echo "#include <tinypy/tp.h>" > $@
#	for name in $(MODULES); do echo "void $${name}_init(TP);" >> $@; done
#	echo "void _tp_import_modules(TP) {" >> $@
#	for name in $(MODULES); do echo "$${name}_init(tp);" >> $@; done
#	echo "}" >> $@

#modules/modules.a: modules/modules.o \
#			$(MODULES_C_FILES:%.c=%.o)
#	$(AR) rcu $@ $^

tinypy/tp.o : tinypy/tp.cpp tinypy/tp*.cpp tinypy/tp*.h

## self hosted compiler is DEPRECATED
#tinypy/compiler.o : $(COMPILER_C_FILES) tinypy/compiler.cpp tinypy/*.h

tinypy/runtime.o : $(RUNTIME_C_FILES) tinypy/runtime.cpp tinypy/*.h


# tpvm only takes compiled byte codes (.bytecode files)
#tpvm : $(VMLIB_FILES:%.c=tinypy/%.o) tinypy/vmmain.o modules/modules.a
<EXE> : $(VMLIB_FILES:%.cpp=tinypy/%.o) tinypy/vmmain.o
	<CC> <EXEOPTS> -o $@ $^ <LIBS>

## broken and DEPRECATED
# tpy takes .py files
#tpy : $(TPLIB_FILES:%.cpp=tinypy/%.o) tinypy/tpmain.o modules/modules.a
#tpy : $(TPLIB_FILES:%.cpp=tinypy/%.o) tinypy/tpmain.o
#	c++ -o $@ $^ -lm

clean:
	rm -rf <EXE>
	rm -rf $(RUNTIME_C_FILES)
	#rm -rf $(COMPILER_C_FILES)
	rm -rf tinypy/*.o
	#rm -rf modules/*/*.o
	#rm -rf modules/*.a
	#rm -rf modules/modules.cpp

'''


def rebuild():
	mode = 'linux'
	exe = 'tpython++'
	exeopts = ''
	CC = 'c++'
	libs = '-lm -ldl -lpython3.7m -lpthread'
	defs = '-DUSE_PYTHON'
	if '--arm' in sys.argv:
		CC = 'arm-linux-gnueabi-g++'
		defs = ''
		libs = '-ldl -lpthread'
		exe += '.arm'
		mode = 'arm'
		exeopts = '-static'
	elif '--windows' in sys.argv or '--mingw' in sys.argv:
		CC = 'x86_64-w64-mingw32-g++-posix'
		defs = ''
		libs = '-lpthread'
		exe += '.exe'
		mode = 'windows'

	if '--debug' in sys.argv:
		defs += ' -DDEBUG'

	makefile = Makefile.replace("<CC>", CC).replace('<DEFINES>', defs).replace('<LIBS>', libs).replace('<EXE>', exe).replace('<EXEOPTS>', exeopts)
	if mode=='windows':
		makefile = makefile.replace('-rdynamic', '')

	open('Makefile', 'wb').write(makefile)
	subprocess.check_call(['make', 'clean'])
	subprocess.check_call(['make'])

	if mode == 'windows':
		for dll in ['libstdc++-6.dll','libgcc_s_seh-1.dll', 'libwinpthread-1.dll']:
			if not os.path.isfile(dll):
				if dll == 'libwinpthread-1.dll':
					os.system('cp -v /usr/x86_64-w64-mingw32/lib/%s ./%s' %(dll, dll))
				else:
					os.system('cp -v /usr/lib/gcc/x86_64-w64-mingw32/5.3-posix/%s ./%s' %(dll, dll))

rebuild()