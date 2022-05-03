.PHONY: watch

all:
	pdflatex -output-directory build main.tex 
	bibtex8 build/main.aux
watch:
	find .  -name "*.tex" | entr -r make

clean:
	rm build/*
