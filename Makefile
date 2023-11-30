EXECUTAVEL = Curtir_ME
PASTAS = Manipuladores ClassesPrincipais
CAMINHOSCPP = $(foreach pasta, $(PASTAS), $(wildcard $(pasta)/*.cpp))
OBJETOS = $(patsubst %.cpp, %.o, $(CAMINHOSCPP))
OBJETOTESTE = testesUnitarios.o

build: test $(EXECUTAVEL)


test: testesUnitarios
	./testesUnitarios

testesUnitarios: $(OBJETOTESTE)
	g++ $^ -o $@

$(OBJETOTESTE): TestesUnitarios/testesUnitarios.cpp
	g++ -w -c $^
	
TestesUnitarios/testesUnitarios.cpp: TestesUnitarios/testesUnitarios.cpp
	g++ -w -c $^


run: $(EXECUTAVEL)
$(EXECUTAVEL): Main.o
	g++ $^ -o $@

Main.o: Main.cpp
	g++ -c $^

Main.cpp: $(OBJETOS)
	g++ -c $^

clean:
	rm -rf *.o $(EXECUTAVEL) testesUnitarios Manipuladores/*.o ClassesPrincipais/*.o
