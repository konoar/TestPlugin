############################################
#
# Plugin Test
#
############################################

TARGETBIN := ./test
TARGETPLG := ./plugin.so

.PHONY: clean run

run: $(TARGETPLG) $(TARGETBIN)
	@$(TARGETBIN)

clean:
	@-rm ./*.o $(TARGETBIN) $(TARGETPLG)

$(TARGETBIN): main.o
	@gcc -o $(TARGETBIN) $^ -ldl

$(TARGETPLG): plugin.o
	@gcc -o $(TARGETPLG) $^ -shared

%.o: %.c
	@gcc -o $@ -c $^

