% : %.cpp template.cpp
	echo "#define RUNDEMO" >> template.cpp
	g++ -static -Wall $< -o $@ -O2
	cat template.cpp | grep -v "#define RUNDEMO" > tmp.cpp
	mv tmp.cpp template.cpp
