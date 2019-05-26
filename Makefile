############################################
#
# Plugin Test
#   copyright 2019.05.23 konoar
#
############################################

TARGETBIN := ./test
TARGETPLG := ./plugin.so

.PHONY: clean run

run: $(TARGETPLG) $(TARGETBIN)
	@-$(TARGETBIN)

clean:
	@-rm ./*.o $(TARGETBIN) $(TARGETPLG)

$(TARGETBIN): common.o main.o
	@gcc -o $(TARGETBIN) $^ -ldl -lpthread

$(TARGETPLG): common.o plugin.o
	@gcc -o $(TARGETPLG) $^ -lpthread -shared

%.o: %.c
	@gcc -o $@ -c $^

