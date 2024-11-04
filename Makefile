TEST_FILES := teste-normal teste-vazio
TEST_DIR := ./teste

all: lzw

# Código principal
lzw: main.c
	$(CC) main.c -o lzw

# Executa todos os testes
# HACK ta meio bizarro esse bash
test: lzw $(TEST_FILES)
	for file in $(TEST_FILES); do ./lzw < $(TEST_DIR)/$$file; done

# Arquivos de teste
teste-normal: $(TEST_DIR)
	echo "Meu texto de teste, 1 2 3!" > $(TEST_DIR)/teste-normal
teste-vazio: $(TEST_DIR)
	touch $(TEST_DIR)/teste-vazio

$(TEST_DIR):
	mkdir -p $(TEST_DIR)

debug: main.c
	$(CC) main.c -o lzw -g

# Misc
clean:
	rm -f lzw $(TEST_DIR)/*
	rmdir $(TEST_DIR)
