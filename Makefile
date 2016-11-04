#lines starting in # are comments

#= to assign variable
#+= will concatenate, eg with flags passed in from the command line
#you can use a variable by prefixing it with $
#if a variable has more than one character then wrap in ()

#$(<@) is the file name of the target, $(<F) is the file name of the first dependency
#$@ is the target, $< is first dependency, $^ is all dependencies
#$(CXX) $(CXXFlags) -o $@ -c $< equivalent to g++ -std=c++11 -Wall -o target -c dependency1
#$(CXX) $(CXXFlags) -o $@ $^ equivalent to g++ -std=c++11 -Wall -o target dependency1 dependency2...

#@ suppresses the actual command from being printed

#target: dependency1 dependency2...
#<single-tab>recipe line 1
#<single-tab>recipe line 2...

#---------------------------------------------------

#compiler and compiler flags
CXX = g++
CXXFlags += -std=c++11 -Wall -Iinc

#directories
bin = bin/
inc = inc/
lib = lib/
obj = obj/
src = src/
tst = src/tests/
tso = obj/tests/
tsb = bin/tests/

#useful shorthands for dependencies
libhead = $(inc)prime32.h $(inc)prime-checks.h 
testhead = $(libhead) $(tst)tests.h $(tst)test-helpers.h $(tst)catch/catch.hpp
testobj = $(tso)test-helpers.o $(lib)prime32.a
allexe = $(bin)demo $(tsb)quick-tests $(tsb)long-tests $(tsb)overnight-tests

sep = @echo -----------

define compile-target-obj
@echo compiling $(<F)
@$(CXX) $(CXXFlags) -o $@ -c $<
@echo $(<F) compiled
$(sep)
endef

define build-target-exe
@echo building $(@F) executable
@$(CXX) $(CXXFlags) -o $@ $^
@echo $(@F) executable built
$(sep)
endef

define make-target-lib
@echo creating static library $(@F)
@ar rcs $@ $^
@echo $(@F) created
$(sep)
endef

define run-dependency
@echo running $(<F)..
@./$<
endef

#---------------------------------------------------

#.PHONY targets don't correspond to any actual file
.PHONY: library demo tquick tlong tovernight all clean

library: $(lib)prime32.a

demo: $(bin)demo
	$(run-dependency)

tquick: $(tsb)quick-tests
	$(run-dependency)

tlong: $(tsb)long-tests
	$(run-dependency)

tovernight: $(tsb)overnight-tests
	$(run-dependency)

all: $(lib)prime32.a $(allexe)

clean:
	@echo removing binaries
	@rm -f $(allexe) $(lib)*.a $(obj)*.o $(tso)*.o
	@echo binaries removed

#---------------------------------------------------

$(bin)demo: $(obj)demo.o $(lib)prime32.a
	$(build-target-exe)

$(obj)demo.o: $(src)demo.cpp $(libhead)
	$(compile-target-obj)



$(tsb)overnight-tests: $(tso)overnight-tests.o $(testobj)
	$(build-target-exe)

$(tso)overnight-tests.o: $(tst)overnight-tests.cpp $(testhead) 
	$(compile-target-obj)

$(tsb)long-tests: $(tso)long-tests.o $(testobj)
	$(build-target-exe)

$(tso)long-tests.o: $(tst)long-tests.cpp $(testhead) 
	$(compile-target-obj)

$(tsb)quick-tests: $(tso)quick-tests.o $(testobj)
	$(build-target-exe)

$(tso)quick-tests.o: $(tst)quick-tests.cpp $(testhead) 
	$(compile-target-obj)
   
$(tso)test-helpers.o: $(tst)test-helpers.cpp $(tst)test-helpers.h
	$(compile-target-obj)



$(lib)prime32.a: $(obj)prime32.o $(obj)prime-checks.o
	$(make-target-lib) 
	
$(obj)prime32.o: $(src)prime32.cpp $(libhead)  
	$(compile-target-obj)
	
$(obj)prime-checks.o: $(src)prime-checks.cpp $(inc)prime-checks.h
	$(compile-target-obj)