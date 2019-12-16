echo "##TEST GRAFOS CICLICOS RELABEL-TO-BACK"
for file in ./test/ciclico/*txt
do
	name=$(basename "$file")
	echo "File: $name "
	./push_relabel "-back" "-test" < $file
done
echo ""
echo "##TEST GRAFOS CICLICOS RELABEL-TO-FRONT"
for file in ./test/ciclico/*txt
do
	name=$(basename "$file")
	echo "File: $name "
	./push_relabel "-front" "-test"< $file
done
echo ""
echo "##TEST GRAFOS ACICLICOS RELABEL-TO-BACK"
for file in ./test/aciclico/*txt
do
	name=$(basename "$file")
	echo "File: $name "
	./push_relabel "-back" "-test" < $file
done
echo ""
echo "##TEST GRAFOS ACICLICOS RELABEL-TO-FRONT"
for file in ./test/aciclico/*txt
do
	name=$(basename "$file")
	echo "File: $name "
	./push_relabel "-front" "-test" < $file
done
