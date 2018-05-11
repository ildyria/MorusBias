MAIN = main
MASKS_DIR = Masks
LIBS = -lm -fopenmp -flto -fwhole-program -fdelete-null-pointer-checks -march=native
CC = gcc
CFLAGS = -Wall -O3 -fopenmp -fdelete-null-pointer-checks -flto -march=native

NO_COLOR="\033[0m"
RED = "\033[31m"
BRIGHTRED = "\033[91m"
YELLOW = "\033[93m"
ORANGE = "\033[33m"
GRAY = "\033[37m"
GREEN = "\033[32m"
BOLD = "\033[1m"

GEN = Masks/masks_mini_morus_640.c Masks/masks_mini_morus_1280.c Masks/masks_morus_640.c Masks/masks_morus_1280.c
GEN_H = $(GEN:%.c=%.h) main.h
MAINS_C = $(wildcard Ciphers/*.c) main.c $(GEN)
UTILITIES_C = $(wildcard Utilities/*.c)

MAINS_H = $(MAINS_C:%.c=%.h)
UTILITIES_H = $(UTILITIES_C:%.c=%.h)

MAINS_OBJECTS = $(MAINS_C:%.c=%.o)
UTILITIES_OBJECTS = $(UTILITIES_C:%.c=%.o)

.PHONY: clean default all

# BUILD TARGETS

default: print_default full
all: full

full: clean gen_masks gen_full_32 $(MAIN)
alpha: clean gen_masks gen_alpha_32 $(MAIN)
beta: clean gen_masks gen_beta_32 $(MAIN)
gamma: clean gen_masks gen_gamma_32 $(MAIN)
delta: clean gen_masks gen_delta_32 $(MAIN)
epsil: clean gen_masks gen_epsil_32 $(MAIN)
appr1: clean gen_masks gen_appr1_32 $(MAIN)
appr2: clean gen_masks gen_appr2_32 $(MAIN)

full_64: clean gen_masks gen_full_64 $(MAIN)
alpha_64: clean gen_masks gen_alpha_64 $(MAIN)
beta_64: clean gen_masks gen_beta_64 $(MAIN)
gamma_64: clean gen_masks gen_gamma_64 $(MAIN)
delta_64: clean gen_masks gen_delta_64 $(MAIN)
epsil_64: clean gen_masks gen_epsil_64 $(MAIN)
appr1_64: clean gen_masks gen_appr1_64 $(MAIN)
appr2_64: clean gen_masks gen_appr2_64 $(MAIN)

full_32_2: clean gen_masks gen_full_32_2 $(MAIN)
alpha_32_2: clean gen_masks gen_alpha_32_2 $(MAIN)
beta_32_2: clean gen_masks gen_beta_32_2 $(MAIN)
gamma_32_2: clean gen_masks gen_gamma_32_2 $(MAIN)
delta_32_2: clean gen_masks gen_delta_32_2 $(MAIN)
epsil_32_2: clean gen_masks gen_epsil_32_2 $(MAIN)
appr1_32_2: clean gen_masks gen_appr1_32_2 $(MAIN)
appr2_32_2: clean gen_masks gen_appr2_32_2 $(MAIN)

full_64_2: clean gen_masks gen_full_64_2 $(MAIN)
alpha_64_2: clean gen_masks gen_alpha_64_2 $(MAIN)
beta_64_2: clean gen_masks gen_beta_64_2 $(MAIN)
gamma_64_2: clean gen_masks gen_gamma_64_2 $(MAIN)
delta_64_2: clean gen_masks gen_delta_64_2 $(MAIN)
epsil_64_2: clean gen_masks gen_epsil_64_2 $(MAIN)
appr1_64_2: clean gen_masks gen_appr1_64_2 $(MAIN)
appr2_64_2: clean gen_masks gen_appr2_64_2 $(MAIN)

print_default:
	@echo $(ORANGE)"Possible build targets:"
	@echo $(YELLOW)
	@echo "\tMini_Morus_640"
	@echo $(GREEN)"\t make full (default)"$(GRAY)
	@echo 				"\t make alpha"
	@echo				 	"\t make beta "
	@echo				 	"\t make gamma"
	@echo				 	"\t make delta"
	@echo				 	"\t make epsil"
	@echo				 	"\t make appr1"
	@echo				 	"\t make appr2"
	@echo $(YELLOW)
	@echo "\tMini_Morus_1280"
	@echo	$(GRAY)"\t make full_64"
	@echo				 "\t make alpha_64"
	@echo				 "\t make beta_64"
	@echo				 "\t make gamma_64"
	@echo				 "\t make delta_64"
	@echo				 "\t make epsil_64"
	@echo				 "\t make appr1_64"
	@echo				 "\t make appr2_64"
	@echo $(YELLOW)
	@echo "\tMorus_640"
	@echo	$(GRAY)"\t make full_32_2"
	@echo				 "\t make alpha_32_2"
	@echo				 "\t make beta_32_2"
	@echo				 "\t make gamma_32_2"
	@echo				 "\t make delta_32_2"
	@echo				 "\t make epsil_32_2"
	@echo				 "\t make appr1_32_2"
	@echo				 "\t make appr2_32_2"
	@echo $(YELLOW)
	@echo "\tMorus_1280"
	@echo	$(GRAY)"\t make full_64_2"
	@echo				 "\t make alpha_64_2"
	@echo				 "\t make beta_64_2"
	@echo				 "\t make gamma_64_2"
	@echo				 "\t make delta_64_2"
	@echo				 "\t make epsil_64_2"
	@echo				 "\t make appr1_64_2"
	@echo				 "\t make appr2_64_2"
	@echo 			 "I will build default target in 3."
	@sleep 1
	@echo 			 "                               2."
	@sleep 1
	@echo 			 "                               1."
	@sleep 1
	@echo $(GREEN)"Building !"$(NO_COLOR)
	@sleep 1


$(MASKS_DIR):
	mkdir -p $(MASKS_DIR)

gen_masks: $(MASKS_DIR) gen_masks.py
	python3 gen_masks.py

# mini_morus_640

gen_full_32: gen_main.py
	python3 gen_main.py full
gen_alpha_32: gen_main.py
	python3 gen_main.py alpha
gen_beta_32: gen_main.py
	python3 gen_main.py beta
gen_gamma_32: gen_main.py
	python3 gen_main.py gamma
gen_delta_32: gen_main.py
	python3 gen_main.py delta
gen_epsil_32: gen_main.py
	python3 gen_main.py epsil
gen_appr1_32: gen_main.py
	python3 gen_main.py appr1
gen_appr2_32: gen_main.py
	python3 gen_main.py appr2

# mini_morus_1280

gen_full_64: gen_main.py
	python3 gen_main.py full 64
gen_alpha_64: gen_main.py
	python3 gen_main.py alpha 64
gen_beta_64: gen_main.py
	python3 gen_main.py beta 64
gen_gamma_64: gen_main.py
	python3 gen_main.py gamma 64
gen_delta_64: gen_main.py
	python3 gen_main.py delta 64
gen_epsil_64: gen_main.py
	python3 gen_main.py epsil 64
gen_appr1_64: gen_main.py
	python3 gen_main.py appr1 64
gen_appr2_64: gen_main.py
	python3 gen_main.py appr2 64

# morus_640

gen_full_32_2: gen_main.py
	python3 gen_main.py full 32 2
gen_alpha_32_2: gen_main.py
	python3 gen_main.py alpha 32 2
gen_beta_32_2: gen_main.py
	python3 gen_main.py beta 32 2
gen_gamma_32_2: gen_main.py
	python3 gen_main.py gamma 32 2
gen_delta_32_2: gen_main.py
	python3 gen_main.py delta 32 2
gen_epsil_32_2: gen_main.py
	python3 gen_main.py epsil 32 2
gen_appr1_32_2: gen_main.py
	python3 gen_main.py appr1 32 2
gen_appr2_32_2: gen_main.py
	python3 gen_main.py appr2 32 2

# morus_1280

gen_full_64_2: gen_main.py
	python3 gen_main.py full 64 2
gen_alpha_64_2: gen_main.py
	python3 gen_main.py alpha 64 2
gen_beta_64_2: gen_main.py
	python3 gen_main.py beta 64 2
gen_gamma_64_2: gen_main.py
	python3 gen_main.py gamma 64 2
gen_delta_64_2: gen_main.py
	python3 gen_main.py delta 64 2
gen_epsil_64_2: gen_main.py
	python3 gen_main.py epsil 64 2
gen_appr1_64_2: gen_main.py
	python3 gen_main.py appr1 64 2
gen_appr2_64_2: gen_main.py
	python3 gen_main.py appr2 64 2

# not required because this is already a dependency.
$(GEN) : $(MASKS_DIR) gen_masks.py
		@echo -n $(ORANGE)
		python3 gen_masks.py
		@echo -n $(NO_COLOR)

%.o: %.c $(UTILITIES_H) $(MAINS_H)
		@echo -n $(ORANGE)
		$(CC) $(CFLAGS) -c $< -o $@
		@echo -n $(NO_COLOR)

$(MAIN): $(GEN) $(MAINS_OBJECTS) $(UTILITIES_OBJECTS)
		@echo -n $(YELLOW)
		$(CC) $(MAINS_OBJECTS) $(UTILITIES_OBJECTS) -Wall $(LIBS) -o $@
		@echo $(GREEN)$(BOLD)"Build completed!"$(NO_COLOR)

# just a test that HW64 is working correctly
testHW: $(UTILITIES_OBJECTS) testHW.o
		$(CC) $(UTILITIES_OBJECTS) testHW.o -Wall $(LIBS) -o $@


clean: gen_masks.py gen_main.py
		@echo $(BRIGHTRED)"cleaning to prevent conflicts."
		@echo -n $(RED)
		-rm -f *.o
		-rm -f */*.o
		-rm -f $(MAIN)
		-rm -f testHW
		-rm -f $(GEN)
		-rm -f $(GEN_H)
		-rm -fr $(MASKS_DIR)
		@echo $(NO_COLOR)
