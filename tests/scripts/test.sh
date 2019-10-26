echo "Iniciando script de teste."
cd ..
echo "Criando pasta de saida, caso não exista..."
mkdir -p output
echo "Excluindo conteúdo da pasta de saída..."
rm output/*
echo "Criando arquivo de validação da saída..."
mkdir -p validation
rm validation/*
for i in {1..10}
do
	echo "Actual output for test case $i is identical to the expected output." >> validation/expected.out
done
cd ../
echo -e "Fazendo a limpeza dos objetos e executáveis...\n"
make clean
echo -e "Iniciando compilação...\n"
make 
echo -e "\nIniciando testes..."
for i in {1..10}
do
	echo "Testando entrada test_cases/in/$i.in"
	./bin/tp2 tests/test_cases/in/$i.in > tests/output/$i.out
	(cmp --silent tests/test_cases/out/$i.out tests/output/$i.out && 
		echo "Actual output for test case $i is identical to the expected output." || 
		echo "Actual output for test case $i differs to the expected output.") >> tests/output/compare.out
done
make clean -s
cd tests
echo "Fim das comparações. Validando o estado final das execuções."
(cmp --silent validation/expected.out output/compare.out && 
		echo "Testes passaram com sucesso." || 
		(echo -e "Algum teste falhou. Confira a saída a seguir:\n" && cat output/compare.out))
