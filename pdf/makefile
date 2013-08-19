all: pdf

pdf: algorithm_list
	./assemble_latex.awk < algorithm_list > insalg.tex
	pdflatex insalg.tex	
clean:
	rm insalg.tex insalg.log insalg.aux
