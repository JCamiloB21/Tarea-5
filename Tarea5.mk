Resultados_hw5.pdf : Resultados_hw5.tex montecarlo.png
    pdflatex $< 
montecarlo.png : Plots.py
    python Plots.py

