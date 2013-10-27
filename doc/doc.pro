TEMPLATE = subdirs

QMAKE_EXTRA_TARGETS += doc

TEX += libczrational.tex
FILE_BASE += libczrational

doc.name = "Make documentation readable"
doc.input = TEX 
doc.output = $${FILE_BASE}.pdf
doc.commands = pdflatex $${FILE_BASE}.tex &&\
               bibtex   $${FILE_BASE} &&\
               pdflatex $${FILE_BASE}.tex && \
               pdflatex $${FILE_BASE}.tex
doc.CONFIG += target_predeps
doc.variable_out = documents.files
QMAKE_CLEAN +=  $${FILE_BASE}.pdf \
$${FILE_BASE}.aux \
$${FILE_BASE}.toc \
$${FILE_BASE}.log \
$${FILE_BASE}.bbl \
$${FILE_BASE}.blg \
$${FILE_BASE}.out \
$${FILE_BASE}.lol
QMAKE_EXTRA_COMPILERS += doc
documents.path = $$PREFIX/share/doc/
documents.CONFIG += no_check_exist
